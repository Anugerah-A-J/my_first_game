#include <allegro5/color.h>
#ifndef WHITE_KING_H
#define WHITE_KING_H
#pragma once

class White_king
{
public:
    White_king();
    void draw() const;
private:
    float cx;
    float cy;
    float r;
    float x1;
    float y1;
    float x2;
    float y2;
    ALLEGRO_COLOR color;
    float thickness;
};

#endif