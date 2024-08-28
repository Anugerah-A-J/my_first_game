#include "Cyan_pawn.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Cyan_pawn::Cyan_pawn(float cx, float cy):
    cx{cx},
    cy{cy},
    r{Parameter::radius},
    color{al_map_rgba_f(0, 1, 1, 1)},
    thickness{Parameter::line_width}
{
}

void Cyan_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, color);
}

bool Cyan_pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Cyan_pawn::get_cx() const
{
    return cx;
}

float Cyan_pawn::get_cy() const
{
    return cy;
}

void Cyan_pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}