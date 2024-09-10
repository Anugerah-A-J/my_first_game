#include "Parameter.h"
#include <allegro5/color.h>
#ifndef CLIPPER_H
#define CLIPPER_H
#pragma once

class Clipper
{
public:
    void draw() const;
private:
    float x1{0}, y1{0}, x2{2 * Parameter::space}, y2{Parameter::window_height};

    float x3{2 * Parameter::space}, y3{0}, x4{Parameter::window_width - 2 * Parameter::space}, y4{Parameter::space};
    
    float x5{Parameter::window_width - 2 * Parameter::space}, y5{0}, x6{Parameter::window_width}, y6{Parameter::window_height};
    
    float x7{2 * Parameter::space}, y7{Parameter::window_height - Parameter::space}, x8{Parameter::window_width - 2 * Parameter::space}, y8{Parameter::window_height};
    
    ALLEGRO_COLOR color{Parameter::window_color()};
};

#endif