#include "Fence.h"
#include <allegro5/allegro_primitives.h>
// #include <iostream>

void Fence::draw() const
{
    al_draw_rectangle(
        shape.get_origin().get_x(),
        shape.get_origin().get_y(),
        shape.get_max().get_x(),
        shape.get_max().get_y(),
        color,
        thickness
    );
}