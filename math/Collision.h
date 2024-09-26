#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#pragma once

class Collision
{
public:
    static void circle_vs_rectangle(Circle& circle, Rectangle& rectangle, const Line& circle_relative_velocity);
    static void circle_inside_rectangle(Circle& inner_circle, Rectangle& outer_rectangle, const Line& circle_relative_velocity);
private:
    static bool intersect(const Line& line1, const Line& line2, float& t);
    static bool intersect(const Line& line, const Circle& circle, float& t);
};