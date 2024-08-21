#include "Circle.h"
#include <allegro5/allegro_primitives.h>

Circle::Circle(float cx, float cy, float r, ALLEGRO_COLOR color, float thickness):
    cx{cx},
    cy{cy},
    r{r},
    color{color},
    thickness{thickness}
{
}

void Circle::draw() const
{
    al_draw_circle(cx, cy, r, color, thickness);
}
