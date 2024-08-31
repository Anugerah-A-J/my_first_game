#include <allegro5/color.h>
#include "Pawn_mover.h"
#ifndef FENCE_H
#define FENCE_H
#pragma once

class Fence
{
public:
    Fence(Pawn_mover* pm);
    void draw() const;
    void check();
private:
    float x1;
    float y1;
    float x2;
    float y2;
    ALLEGRO_COLOR color;
    float thickness;
    Pawn_mover* pm;
};

#endif