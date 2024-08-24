#include "Aim.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Aim::Aim():
    cx{0},
    cy{0},
    r{Parameter::radius},
    color{al_map_rgba_f(1, 1, 1, 0)},
    thickness{Parameter::line_width},
    x{cx},
    y{cy}
{
}

void Aim::draw() const
{
    al_draw_circle(cx, cy, r, color, thickness);
    al_draw_line(cx, cy, x, y, color, thickness);
}

void Aim::set_cx(float cx)
{
    this->cx = cx;
    this->x = cx;
}

void Aim::set_cy(float cy)
{
    this->cy = cy;
    this->y = cy;
}

void Aim::update_x(float mouse_x)
{
    this->x = x;
}

void Aim::update_y(float mouse_y)
{
    this->y = y;
}

void Aim::hide()
{
    color = al_map_rgba_f(1, 1, 1, 0);
}

void Aim::show()
{
    color = al_map_rgba_f(1, 1, 1, 1);
}
