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
}

bool King_cyan::pointed_by(int x, int y) const
{
    Vector v = Vector(x, y) - circle_shape.get_center();

    return v.magsq() <= circle_shape.get_radius() * circle_shape.get_radius();
}

float King_cyan::get_cx() const
{
    return circle_shape.get_center().get_x();
}

float King_cyan::get_cy() const
{
    return circle_shape.get_center().get_y();
}