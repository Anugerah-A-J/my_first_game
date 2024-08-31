#include "Magenta_pawn.h"
#include "Cyan_pawn.h"
#include <vector>
#ifndef PAWN_CONTAINER_H
#define PAWN_CONTAINER_H

#pragma once

class Pawn_container
{
public:
    Pawn_container();
    void draw() const;
    Magenta_pawn* get_magenta_pointed_by(int x, int y) const;
    Cyan_pawn* get_cyan_pointed_by(int x, int y) const;
    void add_magenta(float cx, float cy);
    void add_cyan(float cx, float cy);
    Magenta_pawn* newest_magenta() const;
    Cyan_pawn* newest_cyan() const;
private:
    std::vector<Magenta_pawn> magenta;
    std::vector<Cyan_pawn> cyan;
};

#endif
