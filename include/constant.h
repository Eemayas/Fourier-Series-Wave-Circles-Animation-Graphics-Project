#ifndef CONSTANT_H
#define CONSTANT_H

#include <vector>
#include <unordered_map>
#include <utility>
#define M_PI 3.14159265358979323846

// Constants for window dimensions and rendering settings

// The width of the OpenGL window in pixels
const int WINDOW_WIDTH = 1600;

// The height of the OpenGL window in pixels
const int WINDOW_HEIGHT = 950;

// The maximum depth for nested structures or recursion levels
const int MAX_DEPTH = 10;

// The radius used for drawing circles in the rendering process
const float RADIUS = 100.0f;

// The x-coordinate of the main graph's center in the window
const float MAIN_GRAPH_CENTER_X = 800.0f;

// The number of points used to draw a circle (usually equal to 360 degrees)
const int CIRCLE_POINTS = 360;

// The value of Pi, used in mathematical calculations for drawing circles
#define M_PI 3.14159265358979323846

// Global variables that are defined in another source file (likely constant.cpp)
// These are declared here as extern to allow access across multiple source files

// Number of circles to be rendered, determined by user input
extern int NUMBERS_OF_CIRCLE;

// Maximum number of points for rendering, calculated based on the number of circles
extern int MAX_POINTS;

// The count of points that make up the outermost circle in the rendering
extern int outerPointsCount;

// A vector storing pairs of x and y coordinates representing points on the outermost circle
extern std::vector<std::pair<float, float>> outerPoints;

// A cache storing precomputed x and y coordinates for points on a circle
// The key is the angle (in degrees), and the value is a pair of x and y coordinates
extern std::unordered_map<int, std::pair<float, float>> circlePointsCache;

#endif // CONSTANT_H
