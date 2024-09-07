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
    void resolve();
private:
    void resolve_left();
    void resolve_right();
    void resolve_top();
    void resolve_bottom();
    float x1;
    float y1;
    float x2;
    float y2;
    ALLEGRO_COLOR color;
    float thickness;
    Pawn_mover* pm;
};

#endif