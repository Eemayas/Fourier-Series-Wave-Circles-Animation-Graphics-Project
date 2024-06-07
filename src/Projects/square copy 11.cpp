#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

// Constants for window dimensions and maximum points for the outer circle
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 600;
const int NUMBERS_OF_CIRCLE = 2;
const int MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE;
const int MAX_DEPTH = 10;
const float RADIUS = 100.0f;

// std::pair<float, float> outerPointsArray[MAX_POINTS];
int outerPointsCount = 0;

std::vector<std::pair<float, float>> outerPoints;

// Cache for precomputed circle points
std::unordered_map<int, std::pair<float, float>> circlePointsCache;

void computeCirclePoints()
{
    const int CIRCLE_POINTS = 360;
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float angle = j * (3.14159f / 180.0f);
        circlePointsCache[j] = {std::cos(angle), std::sin(angle)};
    }
}

void drawCirclesLoop(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, int depth = 0)
{
    static float i[MAX_DEPTH] = {0.0f}; // Static array to keep track of the animation state for each depth

    // Ensure depth is within bounds
    if (depth >= MAX_DEPTH)
    {
        std::cerr << "Exceeded maximum depth of recursion" << std::endl;
        return;
    }

    // Draw x-axis
    glBegin(GL_LINES);
    glVertex2f(800, WINDOW_HEIGHT / 2.0f);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f);
    glEnd();

    // Draw y-axis
    glBegin(GL_LINES);
    glVertex2f(800, 50);
    glVertex2f(800, WINDOW_HEIGHT - 50);
    glEnd();

    const int CIRCLE_POINTS = 360;

    // Draw the main circle with small points
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float x = centerX + radius * circlePointsCache[j].first;
        float y = centerY + radius * circlePointsCache[j].second;
        glVertex2f(x, y);
    }
    glEnd();

    // Calculate the index for the moving point on the circle
    int second_circle = static_cast<int>(i[depth]) % CIRCLE_POINTS;
    int starting_index = std::max(static_cast<int>(i[depth]) - 45, 0);

    // Draw the moving point with larger size
    glPointSize(size);
    glBegin(GL_POINTS);
    for (int j = starting_index; j < static_cast<int>(i[depth]); j++)
    {
        float x = centerX + radius * circlePointsCache[j % CIRCLE_POINTS].first;
        float y = centerY + radius * circlePointsCache[j % CIRCLE_POINTS].second;
        glVertex2f(x, y);
    }
    i[depth] += (2.0f / speed);
    glEnd();

    // Draw a line from the center to the moving point
    glBegin(GL_LINES);
    float lineX = centerX + radius * circlePointsCache[second_circle].first;
    float lineY = centerY + radius * circlePointsCache[second_circle].second;
    glVertex2f(centerX, centerY);
    glVertex2f(lineX, lineY);
    glEnd();

    // Recursive call to draw smaller nested circles
    if (loop > 0)
    {
        drawCirclesLoop(lineX, lineY, RADIUS / (1 + (depth + 1) * 2), RADIUS / ((1 + (depth + 1) * 2)), loop - 1, 5, depth + 1);
    }

    // Track the outer points and animate them across the screen
    if (loop == 0)
    {
        if (outerPoints.size() >= MAX_POINTS)
        {
            outerPoints.pop_back();
        }
        if (outerPoints.empty() || outerPoints.front().second != lineY)
        {
            outerPoints.insert(outerPoints.begin(), {800, lineY});
        }
        // Draw a line from the center to the moving point
        glBegin(GL_LINES);
        glVertex2f(outerPoints[0].first, outerPoints[0].second);
        glVertex2f(lineX, lineY);
        glEnd();

        int temp = 0;
        glPointSize(3);
        glBegin(GL_POINTS);
        for (const auto &coord : outerPoints)
        {
            glVertex2f(coord.first + ((0.008f * temp) * speed / (loop + 1)), coord.second);
            temp++;
        }
        glEnd();
    }
}

// Function to handle key events
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
    }
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circle Frame by Frame", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the key callback
    glfwSetKeyCallback(window, keyCallback);

    // Precompute circle points
    computeCirclePoints();

    // Main loop to render the animation
    while (!glfwWindowShouldClose(window))
    {
        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the viewport
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Set the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

        // Set the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw circle frame by frame
        float centerX = WINDOW_WIDTH / 4.0f;
        float centerY = WINDOW_HEIGHT / 2.0f;
        drawCirclesLoop(centerX, centerY, RADIUS, RADIUS, NUMBERS_OF_CIRCLE, 5);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
