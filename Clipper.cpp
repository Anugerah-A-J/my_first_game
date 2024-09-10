#include "Clipper.h"
#include <allegro5/allegro_primitives.h>

void Clipper::draw() const
{
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
    al_draw_filled_rectangle(x3, y3, x4, y4, color);
    al_draw_filled_rectangle(x5, y5, x6, y6, color);
    al_draw_filled_rectangle(x7, y7, x8, y8, color);
}