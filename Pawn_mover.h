#include "Pawn.h"
#ifndef PAWN_MOVER_H
#define PAWN_MOVER_H

#pragma once

class Pawn_mover
{
public:
    Pawn_mover();
    void set_pawn(Pawn* pawn);
    void update_dxdy(float x_start, float y_start, float x_finish, float y_finish);
    void move();
    bool finish() const;
private:
    Pawn* pawn;
    unsigned int pawn_step_count;
    float dx;
    float dy;
};

#endif