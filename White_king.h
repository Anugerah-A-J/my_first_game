#include <allegro5/color.h>
#ifndef WHITE_KING_H
#define WHITE_KING_H
#pragma once

class White_king
{
public:
    White_king();
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;
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