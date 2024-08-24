#include "Fence.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Fence::Fence():
    x1{2 * Parameter::space},
    y1{Parameter::space},
    x2{Parameter::window_width - 2 * Parameter::space},
    y2{Parameter::window_height - Parameter::space},
    color{al_map_rgba_f(1, 0, 0, 1)},
    thickness{Parameter::line_width}
{
}

void Fence::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
}