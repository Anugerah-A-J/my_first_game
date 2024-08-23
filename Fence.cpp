#include "Fence.h"

Fence::Fence():
    Rectangle{
        2 * Parameter::space,
        Parameter::space,
        Parameter::window_width - 2 * Parameter::space,
        Parameter::window_height - Parameter::space,
        al_map_rgba_f(1, 0, 0, 1),
        Parameter::line_width
    }
{
}

// Fence::~Fence()
// {

// }