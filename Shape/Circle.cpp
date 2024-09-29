#include "Circle.h"

Circle::Circle(float cx, float cy, float r)
:
    center{cx, cy},
    radius{nonnegative(r)}
{}

const Vector& Circle::get_center() const
{
    return center;
}

float Circle::get_radius() const
{
    return radius;
}

void Circle::translate(const Vector& how_much)
{
    center += how_much;
}

void Circle::translate_to(const Vector& destination)
{
    center = destination;
}

void Circle::add_to_radius(float how_much)
{
    radius += how_much;
}

float Circle::nonnegative(float f)
{
    return f > 0 ? f : 0;
}