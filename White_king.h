#ifndef WHITE_KING_H
#define WHITE_KING_H
#pragma once

#include "Game.h"

class White_king
{
public:
    White_king();
    // ~White_king();
    const sf::RectangleShape& get_throne() const {return throne;};
    const sf::CircleShape& get_king() const {return king;};
private:
    sf::RectangleShape throne;
    sf::CircleShape king;
};

#endif