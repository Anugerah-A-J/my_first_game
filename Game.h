#include <string>
#include "Fence.h"
#include "King_magenta.h"
#include "King_cyan.h"
#include "Aim.h"
#include "Clipper.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Pawn_container.h"
#pragma once

enum class Turn{ magenta, cyan };

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void draw() const;
    void update_aim(int x, int y);
    void produce_pawn(int x, int y);
    void logic();

    ALLEGRO_TIMER* const timer { al_create_timer(1.0 / 30.0) };
    ALLEGRO_EVENT_QUEUE* const queue { al_create_event_queue() };
    ALLEGRO_DISPLAY* const display { al_create_display(Parameter::window_width(), Parameter::window_height()) };

    Turn turn {Turn::magenta};
    Fence fence {};
    King_magenta magenta_king {};
    King_cyan cyan_king {};
    Aim aim {};
    Clipper clipper {};
    Pawn_container pawn_container {};
    bool finish {false};
    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};