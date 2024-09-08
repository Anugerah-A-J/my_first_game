#include <allegro5/color.h>
#include "Pawn.h"
#include "Parameter.h"
#ifndef FENCE_H
#define FENCE_H
#pragma once

class Fence
{
public:
    void draw() const;
    bool contain(Pawn* pawn);
    void resolve(Pawn* pawn);
private:
    void resolve_left(Pawn* pawn);
    void resolve_right(Pawn* pawn);
    void resolve_top(Pawn* pawn);
    void resolve_bottom(Pawn* pawn);
    float x1            {2 * Parameter::space};
    float y1            {Parameter::space};
    float x2            {Parameter::window_width - 2 * Parameter::space};
    float y2            {Parameter::window_height - Parameter::space};
    ALLEGRO_COLOR color {al_map_rgb_f(1, 0, 0)};
    float thickness     {Parameter::line_width};
};

#endif