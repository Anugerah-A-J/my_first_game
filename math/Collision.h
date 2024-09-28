#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#pragma once

class Collision
{
public:
    static float circle_vs_circle(const Circle& moving_circle, const Circle& nonmoving_circle, const Line& velocity);
    static float circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    static float circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
private:
    static float intersect(const Line& line1, const Line& line2);
    static float intersect(const Line& line, const Circle& circle);
};