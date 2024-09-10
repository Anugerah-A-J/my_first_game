#include "Pawn_container.h"
#include "Parameter.h"
#include <algorithm>

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
}

void Pawn_container::add_cyan(float cx, float cy)
{
	cyan.emplace_back(Pawn(cx, cy, 0, 1, 1));
    moving_pawn = &cyan.back();
}

void Pawn_container::remove_dead_pawn()
{
    magenta.erase(
        std::remove_if(
            magenta.begin(), 
            magenta.end(), 
            [](Pawn& mp){return mp.is_dead();}
        ),
        magenta.end()
    );

    cyan.erase(
        std::remove_if(
            cyan.begin(), 
            cyan.end(), 
            [](Pawn& cp){return cp.is_dead();}
        ),
        cyan.end()
    );
}

bool Pawn_container::dying_pawn_is_empty()
{
    return dying_pawn.size() == 0;
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