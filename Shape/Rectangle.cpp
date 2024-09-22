#include "Rectangle.h"

Rectangle::Rectangle(float o1, float o2, float w, float h)
:
    origin{o1, o2}, size{validate_size(w), validate_size(h)}
{}

const Vector& Rectangle::get_origin() const
{
    return origin;
}

const Vector& Rectangle::get_size() const
{
    return size;
}

const Vector& Rectangle::get_max() const
{
    return origin + size;
}

void Rectangle::translate(const Vector& v)
{
    origin += v;
}

float Rectangle::validate_size(float f)
{
    return f > 0 ? f : 0;
}