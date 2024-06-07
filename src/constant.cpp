#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

// Constants for window dimensions and maximum points for the outer circle
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 950;
const int MAX_DEPTH = 10;
const float RADIUS = 100.0f;
const float MAIN_GRAPH_CENTER_X = 800.0f;
const int CIRCLE_POINTS = 360;

int NUMBERS_OF_CIRCLE = 3;
int MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE;
int outerPointsCount = 0;
std::vector<std::pair<float, float>> outerPoints;
std::unordered_map<int, std::pair<float, float>> circlePointsCache;