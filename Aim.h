#include <allegro5/color.h>
#include "Parameter.h"
#ifndef AIM_H
#define AIM_H
#pragma once

class Aim
{
public:
    void draw() const;
    void set_center(float cx, float cy);
    void update_xy(float mouse_x, float mouse_y);
    float get_cx() const;
    float get_cy() const;
    float get_x() const;
    float get_y() const;
    void magenta();
    void cyan();
    void show();
    void hide();
    bool get_visible() const;
private:
    float cx{0}, cy{0}, r{Parameter::reach_radius};
    float x{0}, y{0};
    float x1{0}, y1{0};
    float x2{0}, y2{0};
    float x3{0}, y3{0};
    ALLEGRO_COLOR color{al_map_rgb_f(1, 0, 1)};
    float thickness{Parameter::line_width};
    bool visible{false};
};

#endif