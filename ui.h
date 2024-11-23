#include "tui.h"
#pragma once

class End : public Dialog_box
{
public:
    End():
        Dialog_box{Vector(param::window_width / 2, param::window_height / 2)}
    {
        add_choice("> Play again");
        add_choice("> Quit");
    }
};