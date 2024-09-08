#include "Magenta_pawn.h"
#include "Cyan_pawn.h"
#include <vector>
#ifndef PAWN_CONTAINER_H
#define PAWN_CONTAINER_H

#pragma once

class Pawn_container
{
public:
    void draw() const;
    Magenta_pawn* get_magenta_pointed_by(int x, int y) const;
    Cyan_pawn* get_cyan_pointed_by(int x, int y) const;
    void add_magenta(float cx, float cy);
    void add_cyan(float cx, float cy);

    // Magenta_pawn* newest_magenta() const;
    // Cyan_pawn* newest_cyan() const;
    // void kill_newest_cyan();
    // void check();

    void move();
    void update_dxdy(float x_finish, float y_finish);
    Pawn* get_moving_pawn() const;
    void kill_moving_pawn();
    void update();
private:
    std::vector<Magenta_pawn> magenta {};
    std::vector<Cyan_pawn> cyan       {};
    Pawn* moving_pawn                 {nullptr};
    std::vector<Pawn*> dying_pawn     {};
};

#endif
