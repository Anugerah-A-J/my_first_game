#include "Pawn_container.h"
#include "Parameter.h"
#include <algorithm>
#include <iostream>
#include <cmath>

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

    float rx{0}, ry{0}, r{0};
    alive_reachable_pawn.clear();

    for (auto& c: cyan)
    {
        rx = c.get_cx() - cx;
        ry = c.get_cy() - cy;
        r = std::sqrt(rx*rx + ry*ry);

        if (r <= Parameter::reach_radius + 2 * Parameter::radius)
            alive_reachable_pawn.push_back(&c);
    }
}

void Pawn_container::add_cyan(float cx, float cy)
{
	cyan.emplace_back(Pawn(cx, cy, 0, 1, 1));
    moving_pawn = &cyan.back();
    moving_pawn->reset_move_step_count();

    float rx{0}, ry{0}, r{0};
    alive_reachable_pawn.clear();

    for (auto& m: magenta)
    {
        rx = m.get_cx() - cx;
        ry = m.get_cy() - cy;
        r = std::sqrt(rx*rx + ry*ry);

        if (r <= Parameter::reach_radius + 2 * Parameter::radius)
            alive_reachable_pawn.push_back(&m);
    }
}

void Pawn_container::remove_dead_pawn()
{
    for (std::vector<Pawn*>::iterator it = dying_pawn.begin(); it != dying_pawn.end();)
    {
        if ((*it)->is_dead() && *it >= &magenta.front() && *it <= &magenta.back())
        {
            magenta.erase(magenta.begin() + (*it - &magenta.front()));
            it = dying_pawn.erase(it);
        }
        else if ((*it)->is_dead() && *it >= &cyan.front() && *it <= &cyan.back())
        {
            cyan.erase(cyan.begin() + (*it - &cyan.front()));
            it = dying_pawn.erase(it);
        }
        else
            ++it;
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
    if (moving_pawn == nullptr)
        return;

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

void Pawn_container::add_moving_pawn_to_dying_pawn()
{
    if (moving_pawn == nullptr)
        return;

    dying_pawn.push_back(moving_pawn);
}

void Pawn_container::add_dying_reachable_pawn_to_dying_pawn()
{
    if (alive_reachable_pawn.empty() || moving_pawn == nullptr)
        return;

    float rx{0}, ry{0}, r{0};

    for (std::vector<Pawn*>::iterator it = alive_reachable_pawn.begin(); it != alive_reachable_pawn.end();)
    {
        rx = (*it)->get_cx() - moving_pawn->get_cx();
        ry = (*it)->get_cy() - moving_pawn->get_cy();
        r = std::sqrt(rx * rx + ry * ry);

        if (r <= Parameter::radius * 2)
        {
            dying_pawn.push_back(*it);
            it = alive_reachable_pawn.erase(it);
        }
        else
            ++it;
    }
}

void Pawn_container::die()
{
    for (auto& d: dying_pawn)
        d->die();
}