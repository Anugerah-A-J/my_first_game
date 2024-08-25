#include "Clipper.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Clipper::Clipper():
    x1{0},
    y1{0},
    x2{2 * Parameter::space},
    y2{Parameter::window_height},

    x3{2 * Parameter::space},
    y3{0},
    x4{Parameter::window_width - 2 * Parameter::space},
    y4{Parameter::space},
    
    x5{Parameter::window_width - 2 * Parameter::space},
    y5{0},
    x6{Parameter::window_width},
    y6{Parameter::window_height},

    x7{2 * Parameter::space},
    y7{Parameter::window_height - Parameter::space},
    x8{Parameter::window_width - 2 * Parameter::space},
    y8{Parameter::window_height},

    color{Parameter::window_color()}
{
}

void Clipper::draw() const
{
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
    al_draw_filled_rectangle(x3, y3, x4, y4, color);
    al_draw_filled_rectangle(x5, y5, x6, y6, color);
    al_draw_filled_rectangle(x7, y7, x8, y8, color);
}