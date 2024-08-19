#ifndef GAME_H
#define GAME_H
#pragma once

#include <SFML/Graphics.hpp>
#include "Fence.h"
#include "White_king.h"
#include "Black_king.h"

class Game
{
public:
    static constexpr unsigned int window_width{1900};
    static constexpr unsigned int window_height{950};
    static constexpr float space{20.f};
    static constexpr float line_width{2.f};
    static constexpr float radius{5.f};
    const sf::Color window_color{17, 17, 17, 255};
    Game();
    // ~Game();
    void run();
private:
    // std::vector<sf::Shape> map;
    Fence fence;
    White_king white_king;
    Black_king black_king;
    sf::RenderWindow window;
};

#endif