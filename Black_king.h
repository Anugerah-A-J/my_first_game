#include <allegro5/color.h>
#ifndef BLACK_KING_H
#define BLACK_KING_H
#pragma once

class Black_king
{
public:
    Black_king();
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;
private:
    float cx;
    float cy;
    float r;
    ALLEGRO_COLOR color;
    float thickness;
    float x1;
    float y1;
    float x2;
    float y2;
};

#endif