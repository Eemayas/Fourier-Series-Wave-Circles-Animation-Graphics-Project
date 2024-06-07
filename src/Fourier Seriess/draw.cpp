#include "draw.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "constant.h"
#include <iostream>

// Draw the Fourier series approximation of the square wave
void draw_square_wave(const std::vector<double> &data, float centerX, float centerY)
{
    drawAxes(centerX, centerY / 2, WINDOW_WIDTH / 2, 150);

    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    int num_points = data.size();
    for (int i = 0; i < MAX_POINTS; ++i)
    {
        double t = centerX + ((0.08 * i * 1.5) / (NUMBERS_OF_CIRCLE + 1));
        glVertex2f(t, centerY / 2 + data[i * 720 / MAX_POINTS] * 100);
    }
    glEnd();
}

// Draw an axis with an arrowhead
void drawAxisWithArrow(float x1, float y1, float x2, float y2)
{
    // Draw the main line of the axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    // Calculate the direction and length of the arrowhead
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    float unitDx = dx / length;
    float unitDy = dy / length;

    // Draw the arrowhead lines
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x2, y2);
    glVertex2f(x2 - 10 * unitDx + 10 * unitDy, y2 - 10 * unitDy - 10 * unitDx);
    glVertex2f(x2, y2);
    glVertex2f(x2 - 10 * unitDx - 10 * unitDy, y2 - 10 * unitDy + 10 * unitDx);
    glEnd();
}

// Draw the main axes with arrowheads at the ends
void drawAxes(float centerX, float centerY, float xAxisLength, float yAxisLength)
{
    drawAxisWithArrow(centerX, centerY, centerX + xAxisLength, centerY);
    drawAxisWithArrow(centerX, centerY, centerX - 50, centerY);
    drawAxisWithArrow(centerX, centerY, centerX, centerY + yAxisLength);
    drawAxisWithArrow(centerX, centerY, centerX, centerY - yAxisLength);
}

// Recursively draw nested circles with connecting lines to illustrate the Fourier series components
void drawCirclesLoop(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, int depth)
{
    static float i[MAX_DEPTH] = {0.0f};

    if (depth >= MAX_DEPTH)
    {
        std::cerr << "Exceeded maximum depth of recursion" << std::endl;
        return;
    }

    // Draw the circle using precomputed points
    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float x = centerX + radius * circlePointsCache[j].first;
        float y = centerY + radius * circlePointsCache[j].second;
        glVertex2f(x, y);
    }
    glEnd();

    // Determine the position of the point on the circle's circumference
    int second_circle = static_cast<int>(i[depth]) % CIRCLE_POINTS;
    int starting_index = std::max(static_cast<int>(i[depth]) - 45, 0);

    // Draw the point moving along the circle's circumference
    glPointSize(size);
    glBegin(GL_POINTS);
    for (int j = starting_index; j < static_cast<int>(i[depth]); j++)
    {
        float x = centerX + radius * circlePointsCache[j % CIRCLE_POINTS].first;
        float y = centerY + radius * circlePointsCache[j % CIRCLE_POINTS].second;
        glVertex2f(x, y);
    }
    i[depth] += (3.0f / speed);
    glEnd();

    // Draw the connecting line from the center of the circle to the moving point
    glBegin(GL_LINES);
    float lineX = centerX + radius * circlePointsCache[second_circle].first;
    float lineY = centerY + radius * circlePointsCache[second_circle].second;
    glVertex2f(centerX, centerY);
    glVertex2f(lineX, lineY);
    glEnd();

    // Recursively draw the next circle
    if (loop > 0)
    {
        drawCirclesLoop(lineX, lineY, RADIUS / (1 + (depth + 1) * 2), RADIUS / ((1 + (depth + 1) * 2)), loop - 1, 5, depth + 1);
    }

    // Store points for drawing the final path
    if (loop == 0)
    {
        if (outerPoints.size() >= MAX_POINTS)
        {
            outerPoints.pop_back();
        }
        if (outerPoints.empty() || outerPoints.front().second != lineY)
        {
            outerPoints.insert(outerPoints.begin(), {MAIN_GRAPH_CENTER_X, lineY});
        }

        // Draw lines connecting the points
        glBegin(GL_LINES);
        glVertex2f(outerPoints[0].first, outerPoints[0].second);
        glVertex2f(lineX, lineY);
        glEnd();

        // Draw the points along the path
        int temp = 0;
        glPointSize(3);
        glBegin(GL_POINTS);
        for (const auto &coord : outerPoints)
        {
            glVertex2f(coord.first + ((0.08 * temp * 2) / (NUMBERS_OF_CIRCLE + 1)), coord.second);
            temp++;
        }
        glEnd();
    }
}
