#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

// Constants for window dimensions and maximum points for the outer circle
constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 600;
constexpr int MAX_POINTS = 2000;

// Global variables for animation and point tracking
float aa = 0;
float bb = 0;
std::pair<float, float> *outerPoints; // a circular queue storing the outer points of size MAX_POINTS
size_t current_index_of_outerPoints = 0;
size_t n_filled_outerPoints = 0; // keeping track of filled outer points initially

void initialize_spaces()
{
    outerPoints = new std::pair<float, float>[MAX_POINTS];
}

void deinitialize_spaces()
{
    delete[] outerPoints;
}

// Function to draw a circle and its nested circles with animation
void drawCircle(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, float *i)
{
    const int CIRCLE_POINTS = 360; // Number of points to define a circle
    static std::pair<float, float> circlePoints[CIRCLE_POINTS];

    // Precompute circle points if not already done
    static bool pointsComputed = false;
    if (!pointsComputed)
    {
        for (int j = 0; j < CIRCLE_POINTS; j++)
        {
            float angle = j * (3.14159f / 180.0f);
            circlePoints[j] = {std::cos(angle), std::sin(angle)};
        }
        pointsComputed = true;
    }

    // Draw the main circle with small points
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float x = centerX + radius * circlePoints[j].first;
        float y = centerY + radius * circlePoints[j].second;
        glVertex2f(x, y);
    }
    glEnd();

    // Calculate the index for the moving point on the circle
    int second_circle = static_cast<int>(*i) % CIRCLE_POINTS;
    int starting_index = std::max(static_cast<int>(*i) - 90, 0);

    // Draw the moving point with larger size
    glPointSize(size);
    glBegin(GL_POINTS);
    for (int j = starting_index; j < static_cast<int>(*i); j++)
    {
        float x = centerX + radius * circlePoints[j % CIRCLE_POINTS].first;
        float y = centerY + radius * circlePoints[j % CIRCLE_POINTS].second;
        glVertex2f(x, y);
    }
    *i += (1.0f / speed);
    glEnd();

    // Draw a line from the center to the moving point
    glBegin(GL_LINES);
    float lineX = centerX + radius * circlePoints[second_circle].first;
    float lineY = centerY + radius * circlePoints[second_circle].second;
    glVertex2f(centerX, centerY);
    glVertex2f(lineX, lineY);
    glEnd();

    // Recursive call to draw smaller nested circles
    if (loop > 0)
    {
        drawCircle(lineX, lineY, radius / 3, radius / 3, loop - 1, 5, &bb);
    }

    // Track the outer points and animate them across the screen
    if (loop == 0)
    {
        current_index_of_outerPoints = (current_index_of_outerPoints + 1) % MAX_POINTS;
        n_filled_outerPoints = (n_filled_outerPoints + 1) % MAX_POINTS;

        if (outerPoints[current_index_of_outerPoints].second != lineY)
        {
            outerPoints[current_index_of_outerPoints] = {800, lineY};
        }

        int temp = 0;

        glPointSize(3);
        glBegin(GL_POINTS);
        size_t iter_count = 0;
        for (size_t i = current_index_of_outerPoints; iter_count <= n_filled_outerPoints; iter_count++)
        {
            glVertex2f(outerPoints[i].first + (0.008f * temp) * speed, outerPoints[i].second);
            temp++;
            i = (i + 1) % MAX_POINTS;

            if (i == current_index_of_outerPoints)
                break;
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
        aa = 0;
        bb = 0;
        n_filled_outerPoints = 0;
        current_index_of_outerPoints = 0;
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

    // Set the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    initialize_spaces();

    // Draw circle frame by frame
    float radius = 100.0f;
    float centerX = WINDOW_WIDTH / 4.0f;
    float centerY = WINDOW_HEIGHT / 2.0f;

    // Main loop to render the animation
    while (!glfwWindowShouldClose(window))
    {
        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT);

        drawCircle(centerX, centerY, radius, radius, 1, 5, &aa);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    deinitialize_spaces();

    // Terminate GLFW
    glfwTerminate();

    return 0;
}