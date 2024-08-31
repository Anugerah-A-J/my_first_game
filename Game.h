#include <string>
#include "Fence.h"
#include "Magenta_king.h"
#include "Cyan_king.h"
#include "Aim.h"
#include "Clipper.h"
#include <allegro5/allegro5.h>
#include <vector>
#include "Pawn_mover.h"
#include "Pawn_container.h"
#ifndef GAME_H
#define GAME_H
#pragma once

enum class Turn{ magenta, cyan };

class Game
{
public:
    Game();
    ~Game();
    void run();
    static void log(const std::string& description);
private:
    void check(bool test, const std::string& description);

    bool al_init_success;
    bool al_init_primitives_addon_success;
    bool al_install_keyboard_success;
    bool al_install_mouse_success;
    
    ALLEGRO_TIMER* const timer;
    ALLEGRO_EVENT_QUEUE* const queue;
    ALLEGRO_DISPLAY* const display;

    Turn turn;

    Clipper clipper;
    Fence fence;
    Magenta_king magenta_king;
    Cyan_king cyan_king;
    Aim aim;
    void update_aim(int x, int y);

    Pawn_container pawn_container;
    Pawn_mover pawn_mover;

    void produce_pawn(unsigned int button, int x, int y);

    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};

#endif
