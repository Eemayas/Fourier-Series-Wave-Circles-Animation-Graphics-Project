#include "draw.h"
#include "render.h"
#include "utils.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "constant.cpp"

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
        // render(window, squareWaveData);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}