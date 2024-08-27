#include <string>
#include "Fence.h"
#include "White_king.h"
#include "Black_king.h"
#include "Aim.h"
#include "Clipper.h"
#include <allegro5/allegro5.h>
#include <vector>
#include "White_pawn.h"
#include "Black_pawn.h"
#ifndef GAME_H
#define GAME_H
#pragma once

enum class Turn{ white, black };

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

    Turn turn;
    
    Clipper clipper;
    Fence fence;
    White_king white_king;
    Black_king black_king;
    Aim aim;
    bool aim_on;
    void update_aim(int x, int y);

    std::vector<White_pawn> white_pawn;
    std::vector<Black_pawn> black_pawn;

    int index_of_pawn_pointed_by(int x, int y);
    void produce_pawn(unsigned int button, int x, int y);

    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
    void log(const std::string& description);
};

#endif