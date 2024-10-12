#include "King_cyan.h"
#include <allegro5/allegro_primitives.h>

void King_cyan::draw() const
{
    al_draw_rectangle(
        rectangle_shape.get_origin().get_x(),
        rectangle_shape.get_origin().get_y(),
        rectangle_shape.get_max().get_x(),
        rectangle_shape.get_max().get_y(),
        color,
        thickness
    );

    al_draw_filled_circle(
        circle_shape.get_center().get_x(),
        circle_shape.get_center().get_y(),
        circle_shape.get_radius(),
        color
    );

    Line top = rectangle_shape.top();
    Line right = rectangle_shape.right();
    Line bottom = rectangle_shape.bottom();
    Line left = rectangle_shape.left();

    Circle top_left = circle_shape;
    Circle top_right = circle_shape;
    Circle bottom_right = circle_shape;
    Circle bottom_left = circle_shape;

    top_left.translate_to(top.get_start());
    top_right.translate_to(top.get_end());
    bottom_right.translate_to(bottom.get_start());
    bottom_left.translate_to(bottom.get_end());

    top.translate(Vector(0, -circle_shape.get_radius()));
    right.translate(Vector(circle_shape.get_radius(), 0));
    bottom.translate(Vector(0, circle_shape.get_radius()));
    left.translate(Vector(-circle_shape.get_radius(), 0));

    al_draw_line(top.get_start().get_x(), top.get_start().get_y(), top.get_end().get_x(), top.get_end().get_y(), color, thickness);
    al_draw_line(right.get_start().get_x(), right.get_start().get_y(), right.get_end().get_x(), right.get_end().get_y(), color, thickness);
    al_draw_line(bottom.get_start().get_x(), bottom.get_start().get_y(), bottom.get_end().get_x(), bottom.get_end().get_y(), color, thickness);
    al_draw_line(left.get_start().get_x(), left.get_start().get_y(), left.get_end().get_x(), left.get_end().get_y(), color, thickness);

    al_draw_circle(top_left.get_center().get_x(), top_left.get_center().get_y(), top_left.get_radius(), color, thickness);
    al_draw_circle(top_right.get_center().get_x(), top_right.get_center().get_y(), top_right.get_radius(), color, thickness);
    al_draw_circle(bottom_right.get_center().get_x(), bottom_right.get_center().get_y(), bottom_right.get_radius(), color, thickness);
    al_draw_circle(bottom_left.get_center().get_x(), bottom_left.get_center().get_y(), bottom_left.get_radius(), color, thickness);
}

bool King_cyan::pointed_by(const Vector& v) const
{
    return (v - circle_shape.get_center()).magsq() <= circle_shape.get_radius() * circle_shape.get_radius();
}

const Vector& King_cyan::get_center() const
{
    return circle_shape.get_center();
}

const Rectangle &King_cyan::get_rectangle_shape() const
{
    return rectangle_shape;
}

const Circle &King_cyan::get_circle_shape() const
{
    return circle_shape;
}
