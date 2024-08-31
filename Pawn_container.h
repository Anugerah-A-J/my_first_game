#include "Magenta_pawn.h"
#include "Cyan_pawn.h"
#ifndef PAWN_H
#define PAWN_H

#pragma once

class Pawn
{
public:
    Pawn();
    void draw() const;
    Magenta_pawn* get_magenta_pointed_by(int x, int y) const;
    Cyan_pawn* get_cyan_pointed_by(int x, int y) const;
private:
    std::vector<Magenta_pawn> magenta_pawn;
    std::vector<Cyan_pawn> cyan_pawn;
};

#endif