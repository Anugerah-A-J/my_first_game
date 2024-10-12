#include <string>
#include "Game_objects/Fence.h"
#include "Game_objects/King_magenta.h"
#include "Game_objects/King_cyan.h"
#include "Game_objects/Aim.h"
#include "Game_objects/Clipper.h"
#include "Game_objects/Pawn.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Math/Collision.h"
#include <set>
#pragma once

class Game
{
public:
    ~Game();
    void run();
private:
    enum class State { choose_and_aim, move_pawn, end };
    enum class Turn { magenta, cyan, end };
    void draw() const;
    void kill_and_delete_pawns();

    void update_aim(State& state);
    void add_pawn(State& state);
    void move_pawn(State& state);

    Vector mouse_coordinate = Vector(0, 0);

    bool success = al_init() &&
        al_init_primitives_addon() &&
        al_install_keyboard() &&
        al_install_mouse();

    ALLEGRO_TIMER* const timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* const queue = al_create_event_queue();
    ALLEGRO_DISPLAY* const display = al_create_display(Parameter::window_width(), Parameter::window_height());

    Turn turn = Turn::magenta;
    State state = State::choose_and_aim;
    Collision collision_engine;

    Fence fence;
    King_magenta king_magenta;
    King_cyan king_cyan;
    Aim aim;
    Clipper clipper{};
    std::vector<Pawn> pawns_magenta;
    std::vector<Pawn> pawns_cyan;
    std::set<Pawn*> dying_pawns;
    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};