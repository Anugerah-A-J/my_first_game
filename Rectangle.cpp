#include "Rectangle.h"
#include <allegro5/allegro_primitives.h>

Rectangle::Rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness):
    x1{x1},
    y1{y1},
    x2{x2},
    y2{y2},
    color{color},
    thickness{thickness}
{
}

void Rectangle::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
}