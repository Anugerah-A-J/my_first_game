#include "White_pawn.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

White_pawn::White_pawn(float cx, float cy):
    cx{cx},
    cy{cy},
    r{Parameter::radius},
    color{al_map_rgba_f(1, 1, 1, 1)}
{
}

void White_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, color);
}

bool White_pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float White_pawn::get_cx() const
{
    return cx;
}

float White_pawn::get_cy() const
{
    return cy;
}

void White_pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}