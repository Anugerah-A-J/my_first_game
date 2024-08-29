#include "Pawn_mover.h"
#include "Parameter.h"
#include "Game.h"

Pawn_mover::Pawn_mover():
    pawn{nullptr},
    pawn_step_count{Parameter::move_step},
    dx{0},
    dy{0}
{
}

void Pawn_mover::set_pawn(Pawn* pawn)
{
    this->pawn = pawn;
    pawn_step_count = 0;
}

void Pawn_mover::update_dxdy(float x_start, float y_start, float x_finish, float y_finish)
{
    dx = (x_finish - x_start) / Parameter::move_step;
    dy = (y_finish - y_start) / Parameter::move_step;
}

void Pawn_mover::move()
{
    if (pawn == nullptr)
        return;
    
    pawn->move(dx, dy);
    pawn_step_count ++;
}

bool Pawn_mover::finish() const
{
    return pawn_step_count == Parameter::move_step;
}
