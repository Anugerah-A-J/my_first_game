#include "tui.h"
#pragma once

class End : public Dialog_box
{
public:
    End():
        Dialog_box{Vector(param::window_width / 2, param::window_height / 2)}
    {
        Add_choice("> Play again");
        Add_choice("> Quit");
    }
};