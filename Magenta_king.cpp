#include "Magenta_king.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Magenta_king::Magenta_king():
    cx{Parameter::window_width - Parameter::space * 3 - Parameter::radius},
    cy{Parameter::window_height / 2},
    r{Parameter::radius},
    x1{Parameter::window_width - (Parameter::space * 2 + Parameter::radius) * 2},
    y1{Parameter::window_height / 2 - Parameter::radius - Parameter::space},
    x2{Parameter::window_width - Parameter::space * 2},
    y2{Parameter::window_height / 2 + Parameter::radius + Parameter::space},
    color{al_map_rgb_f(1, 0, 1)},
    thickness{Parameter::line_width}
{
}

void Magenta_king::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
    al_draw_filled_circle(cx, cy, r, color);
}

bool Magenta_king::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Magenta_king::get_cx() const
{
    return cx;
}

float Magenta_king::get_cy() const
{
    return cy;
}