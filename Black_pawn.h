#include <allegro5/color.h>
#ifndef BLACK_PAWN_H
#define BLACK_PAWN_H

#pragma once

class Black_pawn
{
public:
    Black_pawn(float cx, float cy);
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;
    void move(float dx, float dy);
private:
    float cx;
    float cy;
    float r;
    ALLEGRO_COLOR color;
    float thickness;
};

#endif