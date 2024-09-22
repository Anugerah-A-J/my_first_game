#include <allegro5/color.h>
#include "Parameter.h"
#pragma once

class King_cyan
{
public:
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;
private:
    float cx{Parameter::space * 3 + Parameter::radius};
    float cy{Parameter::window_height / 2};
    float r{Parameter::radius};
    ALLEGRO_COLOR color{al_map_rgb_f(0, 1, 1)};
    float thickness{Parameter::line_width};
    float x1{Parameter::space * 2};
    float y1{Parameter::window_height / 2 - Parameter::radius - Parameter::space};
    float x2{Parameter::space * 2 + Parameter::radius * 2 + Parameter::space * 2};
    float y2{Parameter::window_height / 2 + Parameter::radius + Parameter::space};
};