#include "Fence.h"
#include "Game.h"

Fence::Fence():
    sf::RectangleShape{sf::Vector2f(
        Game::window_width - 4 * Game::space,
        Game::window_height - 2 * Game::space
    )}
{
    move(2 * Game::space, Game::space);
    setFillColor(sf::Color::Transparent);
    setOutlineThickness(Game::line_width);
    setOutlineColor(sf::Color::Red);
}

// Fence::~Fence()
// {

// }