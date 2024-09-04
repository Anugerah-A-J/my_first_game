#include "Pawn_mover.h"
#include "Parameter.h"
#include "Magenta_pawn.h"

Pawn_mover::Pawn_mover(Pawn_container* pawn_container):
	pawn_container{pawn_container},
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
    if (pawn == nullptr || pawn_step_count == Parameter::move_step)
        return;
    
    pawn->move(dx, dy);
    pawn_step_count ++;
}

bool Pawn_mover::is_finish() const
{
    return pawn_step_count == Parameter::move_step;
}

void Pawn_mover::finish()
{
    pawn_step_count = Parameter::move_step;
}

Pawn *Pawn_mover::get_pawn() const
{
    return pawn;
}

void Pawn_mover::kill_pawn()
{
    Magenta_pawn* mp { dynamic_cast<Magenta_pawn*>(pawn) };

    if (mp == nullptr)
        pawn_container->kill_newest_cyan();
    else
        pawn_container->kill_newest_magenta();

    pawn = nullptr;
}

float Pawn_mover::get_dx() const
{
    return dx;
}

float Pawn_mover::get_dy() const
{
    return dy;
}