#include "White_king.h"

White_king::White_king():
    king{
        Parameter::window_width - Parameter::space * 3 - Parameter::radius,
        Parameter::window_height / 2,
        Parameter::radius,
        al_map_rgba_f(1, 1, 1, 1),
    },
    throne{
        Parameter::window_width - (Parameter::space * 2 + Parameter::radius) * 2,
        Parameter::window_height / 2 - Parameter::radius - Parameter::space,
        Parameter::window_width - Parameter::space * 2,
        Parameter::window_height / 2 + Parameter::radius + Parameter::space,
        al_map_rgba_f(1, 1, 1, 1),
        Parameter::line_width
    }
{
}

void White_king::draw() const
{
    king.draw();
    throne.draw();
}

// White_king::~White_king()
// {

// }