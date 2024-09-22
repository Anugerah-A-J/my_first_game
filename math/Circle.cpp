#include "Circle.h"

Circle::Circle(float cx, float cy, float r)
:
    center{cx, cy},
    radius{validate_radius(r)}
{}

const Vector& Circle::get_center() const
{
    return center;
}

float Circle::get_radius() const
{
    return radius;
}

void Circle::translate(const Vector& v)
{
    center += v;
}

float Circle::validate_radius(float f)
{
    return f > 0 ? f : 0;
}