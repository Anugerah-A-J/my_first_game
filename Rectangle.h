#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once

class Rectangle
{
public:
    Rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);
    // ~Rectangle();
    void draw() const;
private:
    float x1; 
    float y1;
    float x2; 
    float y2;
    ALLEGRO_COLOR color;
    float thickness;
};

#endif