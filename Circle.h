#include <allegro5/color.h>
#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

class Circle
{
public:
    Circle(float cx, float cy, float r, ALLEGRO_COLOR color, float thickness);
    // ~Circle();
    void draw() const;
private:
    float cx;
    float cy;
    float r;
    ALLEGRO_COLOR color;
    float thickness;
};

#endif