#include "Rectangle.h"

Rectangle::Rectangle(float ox, float oy, float w, float h)
:
    origin{ox, oy}, size{validate_size(w), validate_size(h)}
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

Line Rectangle::top() const
{
    return Line(
        origin,
        origin + Vector(size.get_x(), 0)
    );
}

Line Rectangle::right() const
{
    return Line(
        origin + Vector(size.get_x(), 0),
        origin + size
    );
}

Line Rectangle::bottom() const
{
    return Line(
        origin + size,
        origin + Vector(0, size.get_y())
    );
}

Line Rectangle::left() const
{
    return Line(
        origin + Vector(0, size.get_y()),
        origin
    );
}

void Rectangle::translate(const Vector& v)
{
    origin += v;
}

void Rectangle::add_size(const Vector& v)
{
    size += v;
}

float Rectangle::validate_size(float f)
{
    return f > 0 ? f : 0;
}