#include "King_magenta.h"
#include <allegro5/allegro_primitives.h>
#include "Intersect.h"

void King_magenta::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
    al_draw_filled_circle(cx, cy, r, color);
}

bool King_magenta::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float King_magenta::get_cx() const
{
    return cx;
}

float King_magenta::get_cy() const
{
    return cy;
}

bool King_magenta::collide(Pawn *pawn)
{
    if (Intersect::)
}