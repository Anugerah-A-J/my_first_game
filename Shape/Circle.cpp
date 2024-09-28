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

void Circle::translate(const Vector& v)
{
    center += v;
}

void Circle::add_radius(float r)
{
    radius += r;
}

void Circle::set_center(const Vector &v)
{
    center = v;
}

float Circle::nonnegative(float f)
{
    return f > 0 ? f : 0;
}