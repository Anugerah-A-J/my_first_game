#include "../Parameter.h"
#include "King.h"
#pragma once

class King_cyan
:
    public King
{
public:
    void draw() const override;
    bool pointed_by(const Vector& v) const override;
    const Vector& get_center() const override;
    const Rectangle& get_rectangle_shape() const override;
    const Circle& get_circle_shape() const override;
private:
    Circle circle_shape = Circle(
        Parameter::space() * 3 + Parameter::radius(),
        Parameter::window_height() / 2,
        Parameter::radius()
    );

    ALLEGRO_COLOR color = Parameter::cyan();

    float thickness = Parameter::line_width();

    Rectangle rectangle_shape = Rectangle(
        Parameter::space() * 2,
        Parameter::window_height() / 2 - Parameter::radius() - Parameter::space(),
        Parameter::radius() * 2 + Parameter::space() * 2,
        Parameter::radius() * 2 + Parameter::space() * 2
    );
};