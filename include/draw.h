#ifndef DRAW_H
#define DRAW_H
#include <vector>
#include <GLFW/glfw3.h>

void drawAxisWithArrow(float x1, float y1, float x2, float y2);
void drawAxes(float centerX, float centerY, float xAxisLength, float yAxisLength);
void drawCirclesLoop(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, int depth = 0);
// Draw the Fourier series approximation of the square wave
void draw_square_wave(const std::vector<double> &data, float centerX, float centerY);

#endif // DRAW_H