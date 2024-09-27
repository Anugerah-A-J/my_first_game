#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#pragma once

class Collision
{
public:
    static void circle_vs_circle(Circle& moving_circle, Circle& nonmoving_circle, Line& velocity);
    static void circle_vs_rectangle(Circle& moving_circle, Rectangle& nonmoving_rectangle, const Line& velocity);
    static void circle_inside_rectangle(Circle& moving_circle, Rectangle& nonmoving_rectangle, const Line& velocity);
private:
    static bool intersect(const Line& line1, const Line& line2, float& t);
    static bool intersect(const Line& line, const Circle& circle, float& t);
};