#include "tui.h"
#pragma once

class End : public Dialog_box
{
public:
    End(const ALLEGRO_FONT* const font):
        Dialog_box{Vector(param::window_width / 2, param::window_height / 2), font}
    {
        Add_choice("> Play again");
        Add_choice("> Quit");
    }
};