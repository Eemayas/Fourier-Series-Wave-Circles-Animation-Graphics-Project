#include "utils.h"
#include "constant.h"
#include <cmath>

/**
 * @brief Generates a Fourier series approximation of a square wave.
 *
 * This function calculates the Fourier series approximation of a square wave using the specified
 * number of terms. The result is a vector of y-values corresponding to the square wave.
 *
 * @param n_terms The number of terms in the Fourier series to include in the approximation.
 *                Only odd terms are used in the series.
 * @param num_points The number of points to generate in the output vector.
 * @return std::vector<double> A vector containing the y-values of the square wave approximation.
 */
std::vector<double> square_wave_fourier(int n_terms, int num_points)
{
    std::vector<double> y(num_points, 0.0); // Initialize a vector of y-values with 0.0

    // Iterate over the odd terms in the Fourier series
    for (int n = 1; n <= n_terms; n += 2)
    {
        // Calculate the contribution of each term at each point
        for (int i = 0; i < num_points; ++i)
        {
            double t = (i) * (3.14159f / 180.0f);  // Convert the index to radians
            y[i] += (4 / (M_PI * n)) * sin(n * t); // Add the contribution of the nth term
        }
    }
    return y; // Return the resulting y-values for the square wave
}

/**
 * @brief Precompute points for a circle and store them in a cache for quick access.
 *
 * This function calculates the x and y coordinates for a set of points evenly distributed
 * along the circumference of a circle. These points are stored in a cache for efficient
 * access during rendering operations, avoiding the need to recompute them multiple times.
 *
 * The points are calculated using the parametric equations of a circle:
 * - x = cos(angle)
 * - y = sin(angle)
 *
 * The angle is incremented by 1 degree (converted to radians) for each point.
 */
void computeCirclePoints()
{
    int CIRCLE_POINTS = 360; // Define the number of points to generate (one for each degree)

    // Calculate the x and y coordinates for each point and store them in the cache
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float angle = j * (3.14159f / 180.0f);                     // Convert the angle from degrees to radians
        circlePointsCache[j] = {std::cos(angle), std::sin(angle)}; // Store the coordinates in the cache
    }
}
