#include "Black_king.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Black_king::Black_king():
    cx{Parameter::space * 3 + Parameter::radius},
    cy{Parameter::window_height / 2},
    r{Parameter::radius},
    color{al_map_rgba_f(1, 1, 1, 1)},
    thickness{Parameter::line_width},
    x1{Parameter::space * 2},
    y1{Parameter::window_height / 2 - Parameter::radius - Parameter::space},
    x2{Parameter::space * 2 + Parameter::radius * 2 + Parameter::space * 2},
    y2{Parameter::window_height / 2 + Parameter::radius + Parameter::space}
{
}

void Black_king::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
    al_draw_circle(cx, cy, r, color, thickness);
}

bool Black_king::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Black_king::get_cx() const
{
    return cx;
}

float Black_king::get_cy() const
{
    return cy;
}