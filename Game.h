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
#pragma once

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    enum class State { magenta, cyan, end };
    void draw() const;
    void mouse_is_moved();
    void mouse_is_left_clicked();
    void logic();
    void kill_and_delete_pawns();

    Vector mouse_coordinate = Vector(0, 0);

    bool success = al_init() &&
        al_init_primitives_addon() &&
        al_install_keyboard() &&
        al_install_mouse();

    ALLEGRO_TIMER* const timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* const queue = al_create_event_queue();
    ALLEGRO_DISPLAY* const display = al_create_display(Parameter::window_width(), Parameter::window_height());

    State state = State::magenta;
    Collision collision_engine;

    Fence fence;
    King_magenta magenta_king;
    King_cyan cyan_king;
    Aim aim;
    Clipper clipper{};
    std::vector<Pawn> pawns_magenta;
    std::vector<Pawn> pawns_cyan;
    std::vector<Pawn*> dying_pawns;
    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};