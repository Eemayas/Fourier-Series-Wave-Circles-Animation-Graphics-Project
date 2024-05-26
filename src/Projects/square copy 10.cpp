#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

// Constants for window dimensions and maximum points for the outer circle
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 600;
const int MAX_POINTS = 5000;

// Global variables for animation and point tracking
float aa = 0;
float bb = 0;

std::pair<float, float> outerPointsArray[MAX_POINTS];
int outerPointsCount = 0;

std::vector<std::pair<float, float>> outerPoints;

// Function to draw a circle and its nested circles with animation
void drawCircle(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, float *i)
{
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

    const int CIRCLE_POINTS = 360; // Number of points to define a circle
    static std::pair<float, float> circlePoints[CIRCLE_POINTS];

    // Precompute circle points if not already done
    static bool pointsComputed = false;
    if (!pointsComputed)
    {
        for (int j = 0; j < CIRCLE_POINTS; ++j)
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
    *i += (2.0f / speed);
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

        // // Calculate the length of the array
        // size_t arrayLength = sizeof(outerPointsArray) / sizeof(outerPointsArray[0]);

        // // Print the length of the array
        // std::cout << "Length of outerPointsArray: " << arrayLength << std::endl;

        // if (outerPointsCount >= MAX_POINTS)
        // {
        //     // Shift elements to make space for the new point
        //     for (int i = 0; i < MAX_POINTS - 1; ++i)
        //     {
        //         outerPointsArray[i] = outerPointsArray[i + 1];
        //     }
        //     outerPointsCount--;
        // }

        // if (outerPointsArray[0].second != lineY)
        // {
        //     // Shift existing elements to the right
        //     for (int i = outerPointsCount - 1; i > 0; i--)
        //     {
        //         outerPointsArray[i] = outerPointsArray[i - 1];
        //     }

        //     // Add the new point at the beginning of the array
        //     outerPointsArray[0] = {800, lineY};

        //     // Increment the count
        //     outerPointsCount++;
        // }

        // int temp = 0;

        // glPointSize(3);
        // glBegin(GL_POINTS);
        // for (int i = 0; i < 10; --i)
        // {
        //     glVertex2f(outerPointsArray[i].first + (0.008f * temp) * speed, outerPointsArray[i].second);
        //     temp++;
        // }
        // glEnd();

        std::cout << "The length of outerPoints is: " << outerPoints.size() << std::endl;

        if (outerPoints.size() >= MAX_POINTS)
        {
            outerPoints.pop_back();
        }
        if (outerPoints.empty() || outerPoints.front().second != lineY)
        {
            outerPoints.insert(outerPoints.begin(), {800, lineY});
        }
        int temp = 0;
        glPointSize(3);
        glBegin(GL_POINTS);
        for (const auto &coord : outerPoints)
        {
            glVertex2f(coord.first + (0.008f * temp) * speed, coord.second);
            temp++;
        }
        glEnd();
    }
}

// std::pair<float, float> outerPointsArray[MAX_POINTS];
// int outerPointsCount = 0;

// // Function to draw a circle and its nested circles with animation
// void drawCircle(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, float *i)
// {
//     // Draw x-axis
//     glBegin(GL_LINES);
//     glVertex2f(800, WINDOW_HEIGHT / 2.0f);
//     glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f);
//     glEnd();

//     // Draw y-axis
//     glBegin(GL_LINES);
//     glVertex2f(800, 50);
//     glVertex2f(800, WINDOW_HEIGHT - 50);
//     glEnd();

//     const int CIRCLE_POINTS = 360;                       // Number of points to define a circle
//     std::pair<float, float> circlePoints[CIRCLE_POINTS]; // Array for circle points

//     // Precompute circle points if not already done
//     static bool pointsComputed = false;
//     if (!pointsComputed)
//     {
//         for (int j = 0; j < CIRCLE_POINTS; ++j)
//         {
//             float angle = j * (3.14159f / 180.0f);
//             circlePoints[j] = {std::cos(angle), std::sin(angle)};
//         }
//         pointsComputed = true;
//     }

//     // Draw the main circle with small points
//     glPointSize(1);
//     glBegin(GL_POINTS);
//     for (int j = 0; j < CIRCLE_POINTS; ++j)
//     {
//         float x = centerX + radius * circlePoints[j].first;
//         float y = centerY + radius * circlePoints[j].second;
//         glVertex2f(x, y);
//     }
//     glEnd();

//     // Calculate the index for the moving point on the circle
//     int second_circle = static_cast<int>(*i) % CIRCLE_POINTS;
//     int starting_index = std::max(static_cast<int>(*i) - 90, 0);

//     // Draw the moving point with larger size
//     glPointSize(size);
//     glBegin(GL_POINTS);
//     for (int j = starting_index; j < static_cast<int>(*i); j++)
//     {
//         float x = centerX + radius * circlePoints[j % CIRCLE_POINTS].first;
//         float y = centerY + radius * circlePoints[j % CIRCLE_POINTS].second;
//         glVertex2f(x, y);
//     }
//     *i += (1.0f / speed);
//     glEnd();

//     // Draw a line from the center to the moving point
//     glBegin(GL_LINES);
//     float lineX = centerX + radius * circlePoints[second_circle].first;
//     float lineY = centerY + radius * circlePoints[second_circle].second;
//     glVertex2f(centerX, centerY);
//     glVertex2f(lineX, lineY);
//     glEnd();

//     // Recursive call to draw smaller nested circles
//     if (loop > 0)
//     {
//         drawCircle(lineX, lineY, radius / 3, radius / 3, loop - 1, 5, &bb);
//     }

//     // Track the outer points and animate them across the screen
//     if (loop == 0)
//     {
//         if (outerPointsCount >= MAX_POINTS)
//         {
//             // Shift elements to make space for the new point
//             for (int i = 0; i < MAX_POINTS - 1; ++i)
//             {
//                 outerPointsArray[i] = outerPointsArray[i + 1];
//             }
//             outerPointsCount--;
//         }

//         // Add the new point to the array
//         outerPointsArray[outerPointsCount++] = {800, lineY};

//         int temp = 0;

//         glPointSize(3);
//         glBegin(GL_POINTS);
//         for (int i = 0; i < outerPointsCount; ++i)
//         {
//             glVertex2f(outerPointsArray[i].first + (0.008f * temp) * speed, outerPointsArray[i].second);
//             temp++;
//         }
//         glEnd();
//     }
// }

// Function to handle key events
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        aa = 0;
        bb = 0;
        // outerPoints.clear();
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
        float radius = 100.0f;
        float centerX = WINDOW_WIDTH / 4.0f;
        float centerY = WINDOW_HEIGHT / 2.0f;
        drawCircle(centerX, centerY, radius, radius, 1, 5, &aa);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

// std::vector<std::pair<float, float>> outerPoints;
// // Function to draw a circle and its nested circles with animation
// void drawCircle(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, float *i)
// {
//     // Draw x-axis
//     glBegin(GL_LINES);
//     glVertex2f(800, WINDOW_HEIGHT / 2.0f);
//     glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f);
//     glEnd();

//     // Draw y-axis
//     glBegin(GL_LINES);
//     glVertex2f(800, 50);
//     glVertex2f(800, WINDOW_HEIGHT - 50);
//     glEnd();

//     const int CIRCLE_POINTS = 360; // Number of points to define a circle
//     static std::pair<float, float> circlePoints[CIRCLE_POINTS];

//     // Precompute circle points if not already done
//     static bool pointsComputed = false;
//     if (!pointsComputed)
//     {
//         for (int j = 0; j < CIRCLE_POINTS; ++j)
//         {
//             float angle = j * (3.14159f / 180.0f);
//             circlePoints[j] = {std::cos(angle), std::sin(angle)};
//         }
//         pointsComputed = true;
//     }

//     // Draw the main circle with small points
//     glPointSize(1);
//     glBegin(GL_POINTS);
//     for (int j = 0; j < CIRCLE_POINTS; ++j)
//     {
//         float x = centerX + radius * circlePoints[j].first;
//         float y = centerY + radius * circlePoints[j].second;
//         glVertex2f(x, y);
//     }
//     glEnd();

//     // Calculate the index for the moving point on the circle
//     int second_circle = static_cast<int>(*i) % CIRCLE_POINTS;
//     int starting_index = std::max(static_cast<int>(*i) - 90, 0);

//     // Draw the moving point with larger size
//     glPointSize(size);
//     glBegin(GL_POINTS);
//     for (int j = starting_index; j < static_cast<int>(*i); j++)
//     {
//         float x = centerX + radius * circlePoints[j % CIRCLE_POINTS].first;
//         float y = centerY + radius * circlePoints[j % CIRCLE_POINTS].second;
//         glVertex2f(x, y);
//     }
//     *i += (1.0f / speed);
//     glEnd();

//     // Draw a line from the center to the moving point
//     glBegin(GL_LINES);
//     float lineX = centerX + radius * circlePoints[second_circle].first;
//     float lineY = centerY + radius * circlePoints[second_circle].second;
//     glVertex2f(centerX, centerY);
//     glVertex2f(lineX, lineY);
//     glEnd();
//     // Recursive call to draw smaller nested circles
//     if (loop > 0)
//     {
//         drawCircle(lineX, lineY, radius / 3, radius / 3, loop - 1, 5, &bb);
//     }
//     // Track the outer points and animate them across the screen
//     if (loop == 0)
//     {
//         if (outerPoints.size() >= MAX_POINTS)
//         {
//             outerPoints.erase(outerPoints.begin());
//         }
//         if (outerPoints.empty() || outerPoints.front().second != lineY)
//         {
//             outerPoints.insert(outerPoints.begin(), {800, lineY});
//         }
//         int temp = 0;
//         glPointSize(3);
//         glBegin(GL_POINTS);
//         for (const auto &coord : outerPoints)
//         {
//             glVertex2f(coord.first + (0.008f * temp) * speed, coord.second);
//             temp++;
//         }
//         glEnd();
//     }
// }
