#include "Black_king.h"

Black_king::Black_king():
    king{
        Parameter::space * 3 + Parameter::radius,
        Parameter::window_height / 2,
        Parameter::radius,
        al_map_rgba_f(1, 1, 1, 1),
        Parameter::line_width
    },
    throne{
        Parameter::space * 2,
        Parameter::window_height / 2 - Parameter::radius - Parameter::space,
        Parameter::space * 2 + Parameter::radius * 2 + Parameter::space * 2,
        Parameter::window_height / 2 + Parameter::radius + Parameter::space,
        al_map_rgba_f(1, 1, 1, 1), 
        Parameter::line_width
    }
{
}

void Black_king::draw() const
{
    king.draw();
    throne.draw();
}

// White_king::~White_king()
// {

// }