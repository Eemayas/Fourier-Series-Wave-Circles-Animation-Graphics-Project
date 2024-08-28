#include "constant.h"

// Define and initialize the number of circles to be drawn in the animation.
int NUMBERS_OF_CIRCLE = 3; 

// Calculate the maximum number of points based on the initial number of circles.
// This value will be updated dynamically in the program based on user input.
int MAX_POINTS = 5000 * NUMBERS_OF_CIRCLE; 

// Initialize the count of points on the outermost circle to zero.
// This will be used to track the number of points drawn for the largest circle.
int outerPointsCount = 0; 

// Initialize an empty vector to store the coordinates of points on the outermost circle.
// Each point is represented as a pair of floats (x, y).
std::vector<std::pair<float, float>> outerPoints; 

// Initialize an empty unordered map to cache the precomputed circle points.
// The key is the angle in degrees, and the value is a pair of floats representing the (x, y) coordinates.
std::unordered_map<int, std::pair<float, float>> circlePointsCache;
