#include "Shapes.hpp"
#pragma once

class King
{
    Circle circle_shape = Circle(
        Parameter::window_width() - Parameter::space() * 3 - Parameter::radius(),
        Parameter::window_height() / 2,
        Parameter::radius()
    );

    ALLEGRO_COLOR color = Parameter::magenta();

    float thickness = Parameter::line_width();

    Rectangle rectangle_shape = Rectangle(
        Parameter::window_width() - (Parameter::space() * 2 + Parameter::radius()) * 2,
        Parameter::window_height() / 2 - Parameter::radius() - Parameter::space(),
        Parameter::radius() * 2 + Parameter::space() * 2,
        Parameter::radius() * 2 + Parameter::space() * 2
    );

    virtual void draw() const = 0;
    virtual bool pointed_by(const Vector& v) const = 0;
    virtual const Vector& get_center() const = 0;
    virtual const Rectangle& get_rectangle_shape() const = 0;
    virtual const Circle& get_circle_shape() const = 0;
};