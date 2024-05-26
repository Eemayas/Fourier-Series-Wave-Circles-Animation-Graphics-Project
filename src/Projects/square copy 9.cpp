#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 600;
float aa = 0;
float ggg = 0;
float bb = 0;
std::vector<std::pair<float, float>> outerPoints;

void drawCircle(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, float *i)
{

    std::vector<std::pair<float, float>> circlePoints;
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int j = 0; j < 360; ++j)
    {
        float angle = j * (3.14159f / 180.0f);
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
        circlePoints.push_back(std::make_pair(x, y));
    }
    glEnd();

    int second_circle = (int)(*i) % 360;

    int starting_index = *i - 90 < 0 ? 0 : *i - 90;

    glPointSize(size);
    glBegin(GL_POINTS);
    for (int j = starting_index; j < (int)(*i); j++)
    {
        glVertex2f(circlePoints[j % 360].first, circlePoints[j % 360].second);
    }

    *i += (1.0f / speed);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(centerX, centerY);
    glVertex2f(circlePoints[second_circle].first, circlePoints[second_circle].second);
    glEnd();

    if (loop > 0)
    {
        drawCircle(circlePoints[second_circle].first, circlePoints[second_circle].second, radius / 3, radius / 3, loop - 1, 5, &bb);
    }
    if (loop == 0)
    {
        // Print the length of the vector
        std::cout << "The length of outerPoints is: " << outerPoints.size() << std::endl;
        if (outerPoints.size() > 2000)
        {
            outerPoints.pop_back();
        }
        else
        {
            if (outerPoints.empty() || outerPoints.front().second != circlePoints[second_circle].second)
            {
                outerPoints.insert(outerPoints.begin(), {800, circlePoints[second_circle].second});
            }
        }
        int temp = 0;

        glPointSize(3);
        glBegin(GL_POINTS);
        for (const auto &coord : outerPoints)
        {
            glVertex2f(coord.first + (0.008 * temp) * speed, coord.second);
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
        aa = 0;
        bb = 0;
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

    int ddddd = 1;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    // while (ddddd <= 100)
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
        float radius = 100.0f;
        float centerX = WINDOW_WIDTH / 4.0f;
        float centerY = WINDOW_HEIGHT / 2.0f;
        drawCircle(centerX, centerY, radius, radius, 2, 5, &aa);

        // // Draw the points
        // drawPoints();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
        ddddd = ddddd + 1;
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}