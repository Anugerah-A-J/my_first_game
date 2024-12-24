#include "tui.hpp"
#pragma once

class End_dialog_box : public Dialog_box
{
public:
    End_dialog_box(const ALLEGRO_FONT *const font)
        : Dialog_box{Vector(Param::window_width / 2, Param::window_height / 2), font}
    {
        Add_choice("> Play again");
        Add_choice("> Quit");
    }
};
