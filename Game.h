#include <string>
#include "Fence.h"
#include "White_king.h"
#include "Black_king.h"
#include "Aim.h"
#ifndef GAME_H
#define GAME_H
#pragma once

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void check(bool test, const std::string& description);

    bool al_init_success;
    bool al_init_primitives_addon_success;
    bool al_install_keyboard_success;
    bool al_install_mouse_success;
    
    ALLEGRO_TIMER* const timer;
    ALLEGRO_EVENT_QUEUE* const queue;
    ALLEGRO_DISPLAY* const display;
    
    Clipper clipper;
    Fence fence;
    White_king white_king;
    Black_king black_king;
    Aim aim;

    void update_aim(int x, int y);
    // White_pawns white_pawns;
    // Black_pawns black_pawns;
    // Boxes boxes;
    // Trees trees;
    // Xs xs;
};

#endif