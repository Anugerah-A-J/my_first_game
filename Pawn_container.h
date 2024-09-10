#include "Pawn.h"
#include <vector>
#ifndef PAWN_CONTAINER_H
#define PAWN_CONTAINER_H

#pragma once

class Pawn_container
{
public:
    void draw() const;
    Pawn* get_magenta_pointed_by(int x, int y) const;
    Pawn* get_cyan_pointed_by(int x, int y) const;
    void add_magenta(float cx, float cy);
    void add_cyan(float cx, float cy);

    void move();
    void stop();
    void update_dxdy(float x_finish, float y_finish);
    Pawn* get_moving_pawn() const;
    void add_dying_pawn(Pawn* pawn);
    // void trigger_dying_magenta();
    // void trigger_dying_cyan();
    void die();
    void remove_dead_pawn();
    bool dying_pawn_is_empty();
private:
    std::vector<Pawn> magenta {};
    std::vector<Pawn> cyan {};
    Pawn* moving_pawn {nullptr}; // set by add_magenta and add_cyan, reset by stop()
    std::vector<Pawn*> dying_pawn {};
    std::vector<Pawn*> reachable_pawn {};
};

#endif
