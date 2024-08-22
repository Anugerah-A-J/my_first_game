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
    // ~Game();
    void run();
private:
    void must_init(bool test, const std::string& description);
    // std::vector<sf::Shape> map;
    Fence fence;
    White_king white_king;
    Black_king black_king;
};

#endif