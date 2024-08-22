#include <allegro5/color.h>

#ifndef FILLED_CIRCLE_H
#define FILLED_CIRCLE_H
#pragma once

class Filled_circle
{
public:
    Filled_circle(float cx, float cy, float r, ALLEGRO_COLOR color);
    // ~Filled_circle();
    void draw() const;
private:
    float cx;
    float cy;
    float r;
    ALLEGRO_COLOR color;
};

#endif