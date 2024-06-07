// #include "render.h"
// #include "draw.h"
// #include "utils.h"
// #include "draw.h"
// #include <GLFW/glfw3.h>
// #include "constant.h"

// // Render the entire scene including circles and square wave approximation
// void render(GLFWwindow *window, const std::vector<double> &squareWaveData)
// {
//     // Clear the buffer
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Set the viewport
//     glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

//     // Set the projection matrix
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

//     // Set the modelview matrix
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     // Draw circle frame by frame
//     float centerX = WINDOW_WIDTH / 4.0f;
//     float centerY = WINDOW_HEIGHT * 3 / 4.0f;
//     drawAxes(MAIN_GRAPH_CENTER_X, centerY, WINDOW_WIDTH / 2, 150);
//     drawCirclesLoop(centerX, centerY, RADIUS, RADIUS, NUMBERS_OF_CIRCLE, 5);

//     // Draw the Fourier series approximation of the square wave
//     glColor3f(0.0f, 1.0f, 0.0f);
//     draw_square_wave(squareWaveData, MAIN_GRAPH_CENTER_X - 360, WINDOW_HEIGHT / 2);

//     // Swap front and back buffers
//     glfwSwapBuffers(window);
// }
