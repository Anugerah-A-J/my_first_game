#include "Pawn.h"
#include <vector>
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
    void add_moving_pawn_to_dying_pawn();
    void add_dying_reachable_pawn_to_dying_pawn();
    void die();
    void remove_dead_pawn();
    bool dying_pawn_is_empty();
    void moving_pawn_is_dead_at_stop();
private:
    bool dead_at_stop{false};
    std::vector<Pawn> magenta {};
    std::vector<Pawn> cyan {};
    Pawn* moving_pawn {nullptr}; // set by add_magenta and add_cyan, reset by stop()
    std::vector<Pawn*> dying_pawn {}; // set by add_moving_pawn_to_dying_pawn() and add_dying_reachable_pawn_to_dying_pawn(), reset by remove_dead_pawn()
    std::vector<Pawn*> alive_reachable_pawn {}; // set and reset by add_magenta() and add_cyan()
};