#include "Pawn_container.h"
#include "Parameter.h"

void Pawn_container::draw() const
{
    for (auto& x : magenta)
        x.draw();

    for (auto& x : cyan)
        x.draw();
}

Magenta_pawn* Pawn_container::get_magenta_pointed_by(int x, int y) const
{
    for (auto& m : magenta)
        if (m.pointed_by(x, y))
            return const_cast<Magenta_pawn*>(&m);
    
    return nullptr;
}

Cyan_pawn* Pawn_container::get_cyan_pointed_by(int x, int y) const
{
    Cyan_pawn* cp {nullptr};

    for (auto& c : cyan)
        if (c.pointed_by(x, y))
            return const_cast<Cyan_pawn*>(&c);

    return nullptr;
}

void Pawn_container::add_magenta(float cx, float cy)
{
	magenta.emplace_back(Magenta_pawn(cx, cy));
    moving_pawn = &magenta.back();
}

void Pawn_container::add_cyan(float cx, float cy)
{
	cyan.emplace_back(Cyan_pawn(cx, cy));
    moving_pawn = &cyan.back();
}

void Pawn_container::update()
{
    for (auto x: dying_pawn)
    {
        if (x == nullptr)
            continue;

        x->dying();

        Magenta_pawn* killed_pawn { dynamic_cast<Magenta_pawn*>(x) };

        if (killed_pawn != nullptr && x->is_dead())
        {
            magenta.pop_back();
            x = nullptr;
        }
        else if (killed_pawn == nullptr && x->is_dead())
        {
            cyan.pop_back();
            x = nullptr;
        }
    }
}

void Pawn_container::move()
{
    if (moving_pawn == nullptr)
        return;
    
    moving_pawn->move();
}

void Pawn_container::update_dxdy(float x_finish, float y_finish)
{
    moving_pawn->update_dxdy(x_finish, y_finish);
}

Pawn *Pawn_container::get_moving_pawn() const
{
    return moving_pawn;
}

void Pawn_container::kill_moving_pawn()
{
    Magenta_pawn* killed_pawn { dynamic_cast<Magenta_pawn*>(moving_pawn) };

    if (killed_pawn == nullptr)
        dying_pawn.emplace_back(&cyan.back());
    else
        dying_pawn.emplace_back(&magenta.back());

    moving_pawn = nullptr;
}