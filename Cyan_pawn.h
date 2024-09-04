#include <allegro5/color.h>
#include "Pawn.h"
#ifndef CYAN_PAWN_H
#define CYAN_PAWN_H

#pragma once

class Cyan_pawn:
     public Pawn
{
public:
    Cyan_pawn(float cx, float cy);
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const override;
    float get_cy() const override;
    void move(float dx, float dy) override;
    bool is_dead() override;
    void dying() override;
private:
    float cx, cy, r;
    float red, green, blue;
};

#endif
