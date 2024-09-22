#include <allegro5/color.h>
#include "Pawn.h"
#include "Parameter.h"
#include "Rectangle.h"
#pragma once

class Fence
{
public:

    void draw() const;

private:

    Rectangle shape = Rectangle(
        2 * Parameter::space(),
        Parameter::space(),
        Parameter::window_width() - 4 * Parameter::space(),
        Parameter::window_height() - 2 * Parameter::space()
    );
    
    ALLEGRO_COLOR color = Parameter::red();

    float thickness = Parameter::line_width();
};