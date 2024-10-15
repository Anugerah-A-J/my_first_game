#include "Shapes.hpp"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "param.hpp"
#pragma once

struct King
{
    Circle shape_circle;
    Rectangle shape_rectangle;
    ALLEGRO_COLOR color;
    float thickness;

    King(const Circle& c, const Rectangle& r, const ALLEGRO_COLOR& color, float thickness)
    :
        shape_circle{c},
        shape_rectangle{r},
        color{color},
        thickness{thickness}
    {};

    void draw() const
    {
        al_draw_rectangle(
            shape_rectangle.start.x,
            shape_rectangle.start.y,
            shape_rectangle.end.x,
            shape_rectangle.end.y,
            color,
            thickness
        );

        al_draw_filled_circle(
            shape_circle.center.x,
            shape_circle.center.y,
            shape_circle.radius,
            color
        );
    };

    bool contain(const Vector& v) const
    {
        return (v - shape_circle.center).magsq <= shape_circle.radius * shape_circle.radius;
    };
};

struct King_magenta:
    public King
{
    King_magenta()
    :
        King{
            Circle(
                param::window_width - param::space * 3 - param::radius,
                param::window_height / 2,
                param::radius
            ),
            Rectangle(
                param::window_width - (param::space * 2 + param::radius) * 2,
                param::window_height / 2 - param::radius - param::space,
                param::radius * 2 + param::space * 2,
                param::radius * 2 + param::space * 2
            ),
            param::magenta,
            param::line_width
        }
    {};
};

struct King_cyan:
    public King
{
    King_cyan()
    :
        King{
            Circle(
                param::space * 3 + param::radius,
                param::window_height / 2,
                param::radius
            ),
            Rectangle(
                param::space * 2,
                param::window_height / 2 - param::radius - param::space,
                param::radius * 2 + param::space * 2,
                param::radius * 2 + param::space * 2
            ),
            param::cyan,
            param::line_width
        }
    {};
};