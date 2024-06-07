#include <iostream>
#include <cmath>
#include <vector>
#include <GLFW/glfw3.h>

// Function to calculate Fourier series approximation of a square wave
std::vector<double> square_wave_fourier(int n_terms, int num_points) {
    std::vector<double> y(num_points, 0.0);
    for (int n = 1; n <= n_terms; n += 2) {  // Only odd harmonics
        for (int i = 0; i < num_points; ++i) {
            double t = 2 * M_PI * i / num_points;
            y[i] += (4 / (M_PI * n)) * sin(n * t);
        }
    }
    return y;
}

// Function to draw the Fourier series approximation of a square wave
void draw_square_wave(const std::vector<double>& data) {
    glBegin(GL_LINE_STRIP);
    int num_points = data.size();
    for (int i = 0; i < num_points; ++i) {
        double t = 2 * M_PI * i / num_points;
        glVertex2d(t, data[i]);
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Fourier Series and Circles", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    

    // Define the number of terms and points
    int n_terms = 10;  // Number of terms in the Fourier series
    int num_points = 1000;  // Number of points to calculate

    // Calculate the Fourier series approximation of the square wave
    std::vector<double> y = square_wave_fourier(n_terms, num_points);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Set the clear color and clear the window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set up the viewport
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Set up the projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 2 * M_PI, -1.5, 1.5, -1.0, 1.0);

        // Set up the modelview
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw the Fourier series approximation of the square wave
        glColor3f(0.0f, 1.0f, 0.0f);
        draw_square_wave(y);


        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
