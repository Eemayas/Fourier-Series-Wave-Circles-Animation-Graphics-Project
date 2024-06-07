#include "utils.h"
#include "constant.cpp"
#include <cmath>

std::vector<double> square_wave_fourier(int n_terms, int num_points)
{
    std::vector<double> y(num_points, 0.0);
    for (int n = 1; n <= n_terms; n += 2)
    {
        for (int i = 0; i < num_points; ++i)
        {
            double t = (i) * (3.14159f / 180.0f);
            y[i] += (4 / (M_PI * n)) * sin(n * t);
        }
    }
    return y;
}

// Precompute points for a circle and cache them for quick access during rendering
void computeCirclePoints()
{
    for (int j = 0; j < CIRCLE_POINTS; ++j)
    {
        float angle = j * (3.14159f / 180.0f);
        circlePointsCache[j] = {std::cos(angle), std::sin(angle)};
    }
}
