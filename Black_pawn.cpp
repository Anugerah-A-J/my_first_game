#include "Black_pawn.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Black_pawn::Black_pawn(float cx, float cy):
    cx{cx},
    cy{cy},
    r{Parameter::radius},
    color{al_map_rgba_f(1, 1, 1, 1)},
    thickness{Parameter::line_width}
{
}

void Black_pawn::draw() const
{
    al_draw_circle(cx, cy, r, color, thickness);
}

bool Black_pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Black_pawn::get_cx() const
{
    return cx;
}

float Black_pawn::get_cy() const
{
    return cy;
}

void Black_pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}