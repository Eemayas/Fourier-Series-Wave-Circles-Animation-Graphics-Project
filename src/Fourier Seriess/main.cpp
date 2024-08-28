#include "draw.h"
#include "utils.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include "constant.h"

/**
 * @brief Callback function for handling keyboard events.
 *
 * This function is triggered when a key event occurs, such as pressing or releasing a key.
 * In this case, pressing the `ESC` key will close the window by signaling GLFW to terminate the main loop.
 *
 * @param window The window that received the event.
 * @param key The keyboard key that was pressed or released.
 * @param scancode The system-specific scan code of the key.
 * @param action GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT.
 * @param mods Bit field describing which modifier keys were held down.
 */
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Signal to close the window
}

/**
 * @brief Main function to set up the window, handle user input, and render an animated scene.
 *
 * This program renders an animated series of circles and a Fourier series approximation of a square wave.
 * The user is prompted to input the number of circles to display, and the square wave is drawn based
 * on this input. The animation updates frame by frame.
 *
 * @return int Exit status of the program (0 for success, -1 for error).
 */
int main()
{
    // Prompt the user for the number of circles
    std::cout << "Enter the number of circles(1-9): ";
    std::cin >> NUMBERS_OF_CIRCLE; // Get user input for the number of circles

    // Update the maximum number of points based on user input
    MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE; // Scale MAX_POINTS to fit the number of circles

    // Initialize the GLFW library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1; // Terminate if initialization fails
    }

    // Create a windowed mode window and an OpenGL context
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circle Frame by Frame", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); // Terminate GLFW if window creation fails
        return -1;
    }

    // Make the window's OpenGL context current
    glfwMakeContextCurrent(window);

    // Set the key callback function to handle keyboard input
    glfwSetKeyCallback(window, keyCallback);

    // Precompute points for rendering circles
    computeCirclePoints();

    // Generate the Fourier series approximation of a square wave
    std::vector<double> squareWaveData = square_wave_fourier(2 * (NUMBERS_OF_CIRCLE + 1), 720);

    // Main loop to render the scene frame by frame
    while (!glfwWindowShouldClose(window))
    {
        // Clear the color buffer to prepare for new frame rendering
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the viewport to cover the entire window
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Set the projection matrix to orthographic (2D)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0); // Map coordinates to window size

        // Set the modelview matrix to identity (no transformations)
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Calculate the center for drawing circles
        float centerX = WINDOW_WIDTH / 4.0f;
        float centerY = WINDOW_HEIGHT * 3 / 4.0f;

        // Draw axes for the main graph
        drawAxes(MAIN_GRAPH_CENTER_X, centerY, WINDOW_WIDTH / 2, 150);

        // Draw multiple circles at calculated positions
        drawCirclesLoop(centerX = centerX, centerY, RADIUS, RADIUS, NUMBERS_OF_CIRCLE, 5);

        // Set color for the square wave (green) and draw the Fourier approximation
        glColor3f(0.0f, 1.0f, 0.0f);
        draw_square_wave(squareWaveData, MAIN_GRAPH_CENTER_X - 360, WINDOW_HEIGHT / 2);

        // Swap front and back buffers to display the rendered frame
        glfwSwapBuffers(window);

        // Poll for and process events (e.g., keyboard input)
        glfwPollEvents();
    }

    // Terminate GLFW and free resources
    glfwTerminate();

    return 0;
}
