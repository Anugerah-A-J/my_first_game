#include "Magenta_pawn.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Magenta_pawn::Magenta_pawn(float cx, float cy):
    cx{cx},
    cy{cy},
    r{Parameter::radius},
    red{1},
    green{0},
    blue{1}
{
}

void Magenta_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, al_map_rgb_f(red, green, blue));
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

bool Magenta_pawn::is_dead() const
{
    return red <= Parameter::window_red &&
        green <= Parameter::window_green &&
        blue <= Parameter::window_blue;
}

void Magenta_pawn::dying()
{
    if (red > Parameter::window_red)
        red -= 0.1;

    if (green > Parameter::window_green)
        green -= 0.1;

    if (blue > Parameter::window_blue)
        blue -= 0.1;
}