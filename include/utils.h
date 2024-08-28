#ifndef UTILS_H
#define UTILS_H

#include <vector>

// Function to calculate the Fourier series approximation of a square wave
// n_terms: Number of terms to use in the Fourier series
// num_points: Number of data points to generate
// Returns a vector of y-values representing the square wave
std::vector<double> square_wave_fourier(int n_terms, int num_points);

// Function to precompute points for a circle and store them in a cache for quick access
// The cached points can be used during rendering to avoid recalculating them multiple times
void computeCirclePoints();

#endif // UTILS_H
