#include <allegro5/color.h>
#ifndef AIM_H
#define AIM_H
#pragma once

class Aim
{
public:
    Aim();
    void draw() const;
    void set_cx(float cx);
    void set_cy(float cy);
    void update_x(float mouse_x);
    void update_y(float mouse_y);
    void hide();
    void show();
private:
    float cx;
    float cy;
    float r;
    ALLEGRO_COLOR color;
    float thickness;
    float x;
    float y;
};

#endif