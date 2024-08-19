#ifndef BLACK_KING_H
#define BLACK_KING_H
#pragma once

#include "Game.h"

class Black_king
{
public:
    Black_king();
    // ~Black_king();
    const sf::RectangleShape& get_throne() const {return throne;};
    const sf::CircleShape& get_king() const {return king;};
private:
    sf::RectangleShape throne;
    sf::CircleShape king;
};

#endif