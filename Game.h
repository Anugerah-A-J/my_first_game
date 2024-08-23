#ifndef GAME_H
#define GAME_H
#pragma once

#include <string>
#include "Fence.h"
#include "White_king.h"
#include "Black_king.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void check(bool test, const std::string& description);
    bool al_init_success;
    bool al_install_keyboard_success;
    bool al_init_primitives_addon_success;
    Fence fence;
    White_king white_king;
    Black_king black_king;
    ALLEGRO_TIMER* const timer;
    ALLEGRO_EVENT_QUEUE* const queue;
    ALLEGRO_DISPLAY* const display;
};

#endif