#include "draw.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "constant.h"
#include <iostream>

/**
 * @brief Draw the Fourier series approximation of a square wave.
 *
 * This function draws the Fourier series approximation of a square wave using the provided data points.
 * It also draws axes for reference.
 *
 * @param data A vector of doubles representing the Fourier series data points for the square wave.
 * @param centerX The x-coordinate of the center point where the wave will be drawn.
 * @param centerY The y-coordinate of the center point where the wave will be drawn.
 */
void draw_square_wave(const std::vector<double> &data, float centerX, float centerY)
{
    // Draw the axes centered at the specified coordinates
    drawAxes(centerX, centerY / 2, WINDOW_WIDTH / 2, 150);

    glColor3f(1.0f, 1.0f, 0.0f); // Set line color to yellow
    glLineWidth(3);              // Set line width
    glBegin(GL_LINE_STRIP);      // Start drawing a connected series of lines

    int num_points = data.size();
    for (int i = 0; i < MAX_POINTS; ++i)
    {
        // Calculate the position of each point in the square wave
        double t = centerX + ((0.08 * i * 1.5) / (NUMBERS_OF_CIRCLE + 1));
        glVertex2f(t, centerY / 2 + data[i * 720 / MAX_POINTS] * 100); // Plot each point
    }
    glEnd(); // Finish drawing the line strip
}

/**
 * @brief Draw a single axis with an arrowhead at the end.
 *
 * This function draws a straight line between two points and adds an arrowhead at the end to
 * represent an axis. The arrowhead is calculated based on the direction and length of the line.
 *
 * @param x1 The x-coordinate of the start point of the axis.
 * @param y1 The y-coordinate of the start point of the axis.
 * @param x2 The x-coordinate of the end point of the axis.
 * @param y2 The y-coordinate of the end point of the axis.
 */
void drawAxisWithArrow(float x1, float y1, float x2, float y2)
{
    // Draw the main axis line
    glColor3f(0.0f, 1.0f, 0.0f); // Set line color to green
    glBegin(GL_LINES);
    glVertex2f(x1, y1); // Start point
    glVertex2f(x2, y2); // End point
    glEnd();

    // Calculate direction and normalize the length
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    float unitDx = dx / length;
    float unitDy = dy / length;

    // Draw the arrowhead lines
    glBegin(GL_LINES);
    glVertex2f(x2, y2);                                                         // Start point of the arrowhead
    glVertex2f(x2 - 10 * unitDx + 10 * unitDy, y2 - 10 * unitDy - 10 * unitDx); // One side of the arrowhead
    glVertex2f(x2, y2);                                                         // Re-start at the end point of the axis
    glVertex2f(x2 - 10 * unitDx - 10 * unitDy, y2 - 10 * unitDy + 10 * unitDx); // Other side of the arrowhead
    glEnd();
}

/**
 * @brief Draw the main coordinate axes with arrowheads at the ends.
 *
 * This function draws the main x-axis and y-axis centered at a given point with arrowheads
 * at the ends. The length of the axes is customizable.
 *
 * @param centerX The x-coordinate of the center point where the axes will be drawn.
 * @param centerY The y-coordinate of the center point where the axes will be drawn.
 * @param xAxisLength The length of the x-axis.
 * @param yAxisLength The length of the y-axis.
 */
void drawAxes(float centerX, float centerY, float xAxisLength, float yAxisLength)
{
    drawAxisWithArrow(centerX, centerY, centerX + xAxisLength, centerY); // Positive x-axis
    drawAxisWithArrow(centerX, centerY, centerX - 50, centerY);          // Negative x-axis
    drawAxisWithArrow(centerX, centerY, centerX, centerY + yAxisLength); // Positive y-axis
    drawAxisWithArrow(centerX, centerY, centerX, centerY - yAxisLength); // Negative y-axis
}

/**
 * @brief Recursively draw nested circles with connecting lines to illustrate the Fourier series components.
 *
 * This function draws a series of nested circles, each representing a component of the Fourier series.
 * The function is recursive and will draw the specified number of loops. The circles have a moving point
 * along their circumference, which is connected to the next circle in the series.
 *
 * @param centerX The x-coordinate of the center of the current circle.
 * @param centerY The y-coordinate of the center of the current circle.
 * @param radius The radius of the current circle.
 * @param speed The speed of the moving point along the circumference.
 * @param loop The number of remaining circles to draw in the series.
 * @param size The size of the point to be drawn on the circumference.
 * @param depth The current recursion depth, used to limit the number of recursive calls.
 */
void drawCirclesLoop(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, int depth)
{
    static float i[MAX_DEPTH] = {0.0f}; // Array to keep track of the angle for each depth

    if (depth >= MAX_DEPTH)
    {
        std::cerr << "Exceeded maximum depth of recursion" << std::endl;
        return;
    }

    // Draw the circle using precomputed points
    glColor3f(1.0f, 1.0f, 0.0f); // Set color to yellow
    glPointSize(1);
    glBegin(GL_POINTS); // Start drawing points
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float x = centerX + radius * circlePointsCache[j].first;
        float y = centerY + radius * circlePointsCache[j].second;
        glVertex2f(x, y);
    }
    glEnd(); // Finish drawing points

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

    // Draw the connecting line from the center of the circle to the moving point (radius)
    glBegin(GL_LINES);
    float lineX = centerX + radius * circlePointsCache[second_circle].first;
    float lineY = centerY + radius * circlePointsCache[second_circle].second;
    glVertex2f(centerX, centerY); // Start point (center of circle)
    glVertex2f(lineX, lineY);     // End point (moving point on circumference)
    glEnd();

    // Recursively draw the next circle
    if (loop > 0)
    {
        drawCirclesLoop(lineX, lineY, RADIUS / (1 + (depth + 1) * 2), RADIUS / ((1 + (depth + 1) * 2)), loop - 1, 5, depth + 1);
    }

    // Store points for drawing the final path (Last Circle)
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
