#include "Pawn_container.h"
#include "Parameter.h"
#include <algorithm>
#include <iostream>

void Pawn_container::draw() const
{
    for (auto& m : magenta)
        m.draw();

    for (auto& c : cyan)
        c.draw();
}

Pawn* Pawn_container::get_magenta_pointed_by(int x, int y) const
{
    for (auto& m : magenta)
        if (m.pointed_by(x, y))
            return const_cast<Pawn*>(&m);
    
    return nullptr;
}

Pawn* Pawn_container::get_cyan_pointed_by(int x, int y) const
{
    for (auto& c : cyan)
        if (c.pointed_by(x, y))
            return const_cast<Pawn*>(&c);

    return nullptr;
}

void Pawn_container::add_magenta(float cx, float cy)
{
	magenta.emplace_back(Pawn(cx, cy, 1, 0, 1));
    moving_pawn = &magenta.back();
    moving_pawn->reset_move_step_count();
}

void Pawn_container::add_cyan(float cx, float cy)
{
	cyan.emplace_back(Pawn(cx, cy, 0, 1, 1));
    moving_pawn = &cyan.back();
    moving_pawn->reset_move_step_count();
}

void Pawn_container::remove_dead_pawn()
{
    for(int i{0}; i < dying_pawn.size(); i++)
    {
        if (dying_pawn.at(i)->is_dead() && dying_pawn.at(i) >= &magenta.front() && dying_pawn.at(i) <= &magenta.back())
        {
            magenta.erase(magenta.begin() + (dying_pawn.at(i) - &magenta.front()));
            dying_pawn.erase(dying_pawn.begin() + i);
        }
        else if (dying_pawn.at(i)->is_dead() && dying_pawn.at(i) >= &cyan.front() && dying_pawn.at(i) <= &cyan.back())
        {
            cyan.erase(cyan.begin() + (dying_pawn.at(i) - &cyan.front()));
            dying_pawn.erase(dying_pawn.begin() + i);
        }
    }
}

bool Pawn_container::dying_pawn_is_empty()
{
    return dying_pawn.empty();
}

void Pawn_container::move()
{
    if (moving_pawn == nullptr)
        return;
    
    moving_pawn->move();
}

void Pawn_container::stop()
{
    moving_pawn->stop();
    moving_pawn = nullptr;
}

void Pawn_container::update_dxdy(float x_finish, float y_finish)
{
    moving_pawn->update_dxdy(x_finish, y_finish);
}

Pawn *Pawn_container::get_moving_pawn() const
{
    return moving_pawn;
}

void Pawn_container::add_dying_pawn(Pawn* pawn)
{
    if (pawn == nullptr)
        return;

    dying_pawn.emplace_back(pawn);
}

void Pawn_container::die()
{
    for (auto& d: dying_pawn)
        d->die();
}