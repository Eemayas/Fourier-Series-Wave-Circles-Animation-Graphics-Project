#include "constant.h"

// Non-const variables need to be defined in exactly one source file
int NUMBERS_OF_CIRCLE = 3;
int MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE;
int outerPointsCount = 0;
std::vector<std::pair<float, float>> outerPoints;
std::unordered_map<int, std::pair<float, float>> circlePointsCache;
