#include <allegro5/color.h>
#include "Parameter.h"
#ifndef KING_MAGENTA_H
#define KING_MAGENTA_H
#pragma once

class King_magenta
{
public:
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;
private:
    float cx{Parameter::window_width - Parameter::space * 3 - Parameter::radius};
    float cy{Parameter::window_height / 2};
    float r{Parameter::radius};
    float x1{Parameter::window_width - (Parameter::space * 2 + Parameter::radius) * 2};
    float y1{Parameter::window_height / 2 - Parameter::radius - Parameter::space};
    float x2{Parameter::window_width - Parameter::space * 2};
    float y2{Parameter::window_height / 2 + Parameter::radius + Parameter::space};
    ALLEGRO_COLOR color{al_map_rgb_f(1, 0, 1)};
    float thickness{Parameter::line_width};
};

#endif