#include "Cyan_pawn.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Cyan_pawn::Cyan_pawn(float cx, float cy):
    cx{cx},
    cy{cy},
    r{Parameter::radius},
    red{0},
    green{1},
    blue{1}
{
}

void Cyan_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, al_map_rgb_f(red, green, blue));
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

bool Cyan_pawn::is_dead() const
{
    return red <= Parameter::window_red &&
        green <= Parameter::window_green &&
        blue <= Parameter::window_blue;
}

void Cyan_pawn::dying()
{
    if (red > Parameter::window_red)
        red -= 0.1;

    if (green > Parameter::window_green)
        green -= 0.1;

    if (blue > Parameter::window_blue)
        blue -= 0.1;
}