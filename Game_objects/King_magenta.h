#include "Parameter.h"
#include "../Shape/Circle.h"
#include "../Shape/Rectangle.h"
#pragma once

class King_magenta
{
public:
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;
private:
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
};