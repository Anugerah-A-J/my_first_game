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
    float cx; float cy;
    float r;
    float x; float y;
    float x1; float y1;
    float x2; float y2;
    float x3; float y3;
    ALLEGRO_COLOR color;
    float thickness;
    bool visible;
};

#endif