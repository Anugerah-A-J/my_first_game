#include <allegro5/color.h>
#include <array>
#ifndef AIM_H
#define AIM_H
#pragma once

class Aim
{
public:
    Aim();
    void draw() const;
    void set_center(float cx, float cy);
    void update_xy(float mouse_x, float mouse_y);
    // void hide();
    // void show();
    float get_cx() const;
    float get_cy() const;
    float get_x() const;
    float get_y() const;
    void magenta();
    void cyan();
private:
    float cx;
    float cy;
    float r;
    ALLEGRO_COLOR color;
    float thickness;
    float x;
    float y;
    std::array<float, 12> xs; // 12 like clock
    std::array<float, 12> ys; // 12 like clock
};

#endif