#include "Pawn_container.h"

Pawn_container::Pawn_container():
    magenta{},
    cyan{}
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
    for (auto& mp : magenta)
        if (mp.pointed_by(x, y))
            return &x;
    
    return nullptr;
}

Cyan_pawn* Pawn_container::get_cyan_pointed_by(int x, int y) const
{
    for (auto& cp : cyan)
        if (cp.pointed_by(x, y))
            return &x;

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
	return magenta.back();
}

Cyan_pawn* Pawn_container::newest_cyan() const
{
	return cyan.back();
}
