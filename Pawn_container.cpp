#include "Pawn_container.h"

Pawn_container::Pawn_container():
    magenta{},
    cyan{},
    magenta_dying_pawn{nullptr},
    cyan_dying_pawn{nullptr}
{
}

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
}

void Pawn_container::add_cyan(float cx, float cy)
{
	cyan.emplace_back(Cyan_pawn(cx, cy));
}

Magenta_pawn* Pawn_container::newest_magenta() const
{
    return const_cast<Magenta_pawn*>(&magenta.back());
}

Cyan_pawn* Pawn_container::newest_cyan() const
{
	return const_cast<Cyan_pawn*>(&cyan.back());
}

void Pawn_container::kill_newest_magenta()
{
    magenta_dying_pawn = &magenta.back();
}

void Pawn_container::kill_newest_cyan()
{
    cyan_dying_pawn = &cyan.back();
}

void Pawn_container::update()
{
    if (magenta_dying_pawn != nullptr)
    {
        magenta_dying_pawn->dying();

        if (magenta_dying_pawn->is_dead())
        {
            magenta.pop_back();
            magenta_dying_pawn = nullptr;
        }
    }
    else if (cyan_dying_pawn != nullptr)
    {
        cyan_dying_pawn->dying();

        if (cyan_dying_pawn->is_dead())
        {
            cyan.pop_back();
            cyan_dying_pawn = nullptr;
        }
    }
}