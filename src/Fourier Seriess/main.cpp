#include "draw.h"
#include "utils.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include "constant.h"

// Handle keyboard events
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    // Ask user for the number of circles
    std::cout << "Enter the number of circles: ";
    std::cin >> NUMBERS_OF_CIRCLE;

    // Update MAX_POINTS based on user input
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

    // Set the key callback to handle keyboard events
    glfwSetKeyCallback(window, keyCallback);

    // Precompute points for drawing circles
    computeCirclePoints();
    std::vector<double> squareWaveData = square_wave_fourier(2 * (NUMBERS_OF_CIRCLE + 1), 720);

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
        drawCirclesLoop(centerX = centerX, centerY, RADIUS, RADIUS, NUMBERS_OF_CIRCLE, 5);

        // Draw the Fourier series approximation of the square wave
        glColor3f(0.0f, 1.0f, 0.0f);
        draw_square_wave(squareWaveData, MAIN_GRAPH_CENTER_X - 360, WINDOW_HEIGHT / 2);

        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}