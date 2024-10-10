#include "King_magenta.h"
#include <allegro5/allegro_primitives.h>

void King_magenta::draw() const
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
}

bool King_magenta::pointed_by(const Vector& v) const
{
    return (v - circle_shape.get_center()).magsq() <= circle_shape.get_radius() * circle_shape.get_radius();
}

const Vector& King_magenta::get_center() const
{
    return circle_shape.get_center();
}

const Rectangle &King_magenta::get_rectangle_shape() const
{
    return rectangle_shape;
}

const Circle &King_magenta::get_circle_shape() const
{
    return circle_shape;
}
