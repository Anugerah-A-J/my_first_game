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
};