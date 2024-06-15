#ifndef CONSTANT_H
#define CONSTANT_H

#include <vector>
#include <unordered_map>
#include <utility>
#define M_PI 3.14159265358979323846

// Constants for window dimensions and maximum points for the outer circle
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 950;
const int MAX_DEPTH = 10;
const float RADIUS = 100.0f;
const float MAIN_GRAPH_CENTER_X = 800.0f;
const int CIRCLE_POINTS = 360;

extern int NUMBERS_OF_CIRCLE;
extern int MAX_POINTS;
extern int outerPointsCount;
extern std::vector<std::pair<float, float>> outerPoints;
extern std::unordered_map<int, std::pair<float, float>> circlePointsCache;

#endif // CONSTANT_H
