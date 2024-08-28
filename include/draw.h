#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <GLFW/glfw3.h>

// Function to draw a single axis with an arrow at the end
// x1, y1: Start coordinates of the axis
// x2, y2: End coordinates of the axis
void drawAxisWithArrow(float x1, float y1, float x2, float y2);

// Function to draw both the X and Y axes with arrows at their ends
// centerX, centerY: Coordinates for the origin of the axes
// xAxisLength: Length of the X-axis
// yAxisLength: Length of the Y-axis
void drawAxes(float centerX, float centerY, float xAxisLength, float yAxisLength);

// Function to draw multiple concentric circles in a loop
// centerX, centerY: Coordinates for the center of the circles
// radius: Radius of the initial circle
// speed: Speed at which the circles are drawn (used for animations)
// loop: Number of circles to be drawn
// size: Line width of the circles
// depth: Current recursion depth, default is 0
void drawCirclesLoop(float centerX, float centerY, float radius, float speed, int loop, GLfloat size, int depth = 0);

// Function to draw the Fourier series approximation of a square wave
// data: The Fourier series data points to be plotted
// centerX, centerY: Coordinates for the origin of the graph
void draw_square_wave(const std::vector<double> &data, float centerX, float centerY);

#endif // DRAW_H
