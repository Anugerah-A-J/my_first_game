#include "../Shape/Circle.h"
#include "../Shape/Rectangle.h"
#pragma once

class King
{
public:
    virtual void draw() const = 0;
    virtual bool pointed_by(const Vector& v) const = 0;
    virtual const Vector& get_center() const = 0;
    virtual const Rectangle& get_rectangle_shape() const = 0;
    virtual const Circle& get_circle_shape() const = 0;
};