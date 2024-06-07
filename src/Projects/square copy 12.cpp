#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

// Constants for window dimensions and maximum points for the outer circle
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 950;
int NUMBERS_OF_CIRCLE = 3;
int MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE;
const int MAX_DEPTH = 10;
const float RADIUS = 100.0f;
const float MAIN_GRAPH_CENTER_X = 800.0f;
const int CIRCLE_POINTS = 360;

// std::pair<float, float> outerPointsArray[MAX_POINTS];
int outerPointsCount = 0;

std::vector<std::pair<float, float>> outerPoints;

// Cache for precomputed circle points
std::unordered_map<int, std::pair<float, float>> circlePointsCache;

void computeCirclePoints()
{
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float angle = j * (3.14159f / 180.0f);
        circlePointsCache[j] = {std::cos(angle), std::sin(angle)};
    }
}

void drawAxisWithArrow(float x1, float y1, float x2, float y2)
{
    // Draw the main line of the arrow
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    // Calculate the direction of the arrow
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    float unitDx = dx / length;
    float unitDy = dy / length;

    // Draw the arrowhead
    glBegin(GL_LINES);
    glVertex2f(x2, y2);
    glVertex2f(x2 - 10 * unitDx + 10 * unitDy, y2 - 10 * unitDy - 10 * unitDx);
    glVertex2f(x2, y2);
    glVertex2f(x2 - 10 * unitDx - 10 * unitDy, y2 - 10 * unitDy + 10 * unitDx);
    glEnd();
}

void drawAxes(float centerX, float centerY, float xAxisLength, float yAxisLength)
{
    // Draw x-axis
    drawAxisWithArrow(centerX, centerY, centerX + xAxisLength, centerY);
    drawAxisWithArrow(centerX, centerY, centerX - 50, centerY);

    // Draw y-axis
    drawAxisWithArrow(centerX, centerY, centerX, centerY + yAxisLength);
    drawAxisWithArrow(centerX, centerY, centerX, centerY - yAxisLength);
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
            outerPoints.insert(outerPoints.begin(), {MAIN_GRAPH_CENTER_X, lineY});
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
            // glVertex2f(coord.first + ((0.08 * temp) / (loop + 1)), coord.second);

            glVertex2f(coord.first + ((0.08 * temp * 2) / (NUMBERS_OF_CIRCLE + 1)), coord.second);
            // std::cout << (0.08 * temp * 2) / (NUMBERS_OF_CIRCLE + 1) << std::endl;
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

// Function to calculate Fourier series approximation of a square wave
std::vector<double> square_wave_fourier(int n_terms, int num_points)
{
    std::vector<double> y(num_points, 0.0);
    for (int n = 1; n <= n_terms; n += 2)
    { // Only odd harmonics
        for (int i = 0; i < num_points; ++i)
        {
            double t = (i) * (3.14159f / 180.0f);
            y[i] += (4 / (M_PI * n)) * sin(n * t);
        }
    }
    return y;
}

// Function to draw the Fourier series approximation of a square wave
void draw_square_wave(const std::vector<double> &data, float centerX, float centerY)
{
    drawAxes(centerX, centerY / 2, WINDOW_WIDTH / 2, 150);

    glBegin(GL_LINE_STRIP);
    int num_points = data.size();
    for (int i = 0; i < MAX_POINTS; ++i)
    {
        double t = centerX + ((0.08 * i * 1.5) / (NUMBERS_OF_CIRCLE + 1));
        glVertex2f(t, centerY / 2 + data[i * 720 / MAX_POINTS] * 100);
    }
    glEnd();
}

int main()
{
    // Ask user for the number of circles
    std::cout << "Enter the number of circles: ";
    std::cin >> NUMBERS_OF_CIRCLE;

    // Update MAX_POINTS and allocate memory for outerPointsArray
    MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE;

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
    std::vector<double> y = square_wave_fourier(2 * (NUMBERS_OF_CIRCLE + 1), 720);

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
        float centerY = WINDOW_HEIGHT * 3 / 4.0f;
        drawAxes(MAIN_GRAPH_CENTER_X, centerY, WINDOW_WIDTH / 2, 150);
        drawCirclesLoop(centerX, centerY, RADIUS, RADIUS, NUMBERS_OF_CIRCLE, 5);

        // Draw the Fourier series approximation of the square wave
        glColor3f(0.0f, 1.0f, 0.0f);
        draw_square_wave(y, MAIN_GRAPH_CENTER_X - 360, WINDOW_HEIGHT / 2);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
