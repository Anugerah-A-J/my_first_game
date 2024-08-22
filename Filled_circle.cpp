#include "Filled_circle.h"
#include <allegro5/allegro_primitives.h>

Filled_circle::Filled_circle(float cx, float cy, float r, ALLEGRO_COLOR color):
    cx{cx},
    cy{cy},
    r{r},
    color{color}
{
}

void Filled_circle::draw() const
{
    al_draw_filled_circle(cx, cy, r, color);
}