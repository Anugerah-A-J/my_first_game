#include "Rectangle.h"

Rectangle::Rectangle(float ox, float oy, float w, float h)
:
    origin{ox, oy},
    size{nonnegative(w), nonnegative(h)}
{
}

const Vector &Rectangle::get_origin() const
{
    return origin;
}

const Vector& Rectangle::get_size() const
{
    return size;
}

const Vector Rectangle::get_max() const
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

void Rectangle::translate(const Vector& how_much)
{
    origin += how_much;
}

void Rectangle::add_to_size(const Vector& how_much)
{
    size += how_much;
}

float Rectangle::nonnegative(float f)
{
    return f > 0 ? f : 0;
}