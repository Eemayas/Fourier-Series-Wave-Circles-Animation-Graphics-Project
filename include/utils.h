#ifndef UTILS_H
#define UTILS_H

#include <vector>

std::vector<double> square_wave_fourier(int n_terms, int num_points);

// Precompute points for a circle and cache them for quick access during rendering
void computeCirclePoints();

#endif // UTILS_H
