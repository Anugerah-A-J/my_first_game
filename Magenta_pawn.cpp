#include "Magenta_pawn.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Magenta_pawn::Magenta_pawn(float cx, float cy):
    cx{cx},
    cy{cy},
    r{Parameter::radius},
    color{al_map_rgba_f(1, 0, 1, 1)}
{
}

void Magenta_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, color);
}

bool Magenta_pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Magenta_pawn::get_cx() const
{
    return cx;
}

float Magenta_pawn::get_cy() const
{
    return cy;
}

void Magenta_pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}