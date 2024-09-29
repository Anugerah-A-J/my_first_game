#include "../Parameter.h"
#include "../Shape/Rectangle.h"
#include <allegro5/color.h>
#pragma once

class Clipper
{
public:
    void draw() const;
private:
    Rectangle left_clipper = Rectangle(
        0,
        0,
        2 * Parameter::space(),
        Parameter::window_height()
    );
    
    Rectangle top_clipper = Rectangle(
        0,
        0,
        Parameter::window_width(),
        Parameter::space()
    );
    
    Rectangle right_clipper = Rectangle(
        Parameter::window_width() - 2 * Parameter::space(),
        0,
        2 * Parameter::space(),
        Parameter::window_height()
    );
    
    Rectangle bottom_clipper = Rectangle(
        0,
        Parameter::window_height() - Parameter::space(),
        Parameter::window_width(),
        Parameter::space()
    );
    
    ALLEGRO_COLOR color = Parameter::black();
};