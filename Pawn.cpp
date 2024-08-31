#include "Pawn.h"

Pawn::Pawn():
    magenta_pawn{},
    cyan_pawn{}
{
}

void Pawn::draw() const
{
    for (auto& x : magenta_pawn)
        x.draw();

    for (auto& x : cyan_pawn)
        x.draw();
}

Magenta_pawn* Pawn::get_magenta_pointed_by(int x, int y) const
{
    for (auto& x : magenta_pawn)
        if (x.pointed_by(x, y))
            return &x;
    
    return nullptr;
}

Cyan_pawn* Pawn::get_cyan_pointed_by(int x, int y) const
{
    for (auto& x : cyan_pawn)
        if (x.pointed_by(x, y))
            return &x;

    return nullptr;
}
