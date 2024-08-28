#include <allegro5/color.h>
#ifndef MAGENTA_PAWN_H
#define MAGENTA_PAWN_H

#pragma once

class Magenta_pawn
{
public:
    Magenta_pawn(float cx, float cy);
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
};

#endif