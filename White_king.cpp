#include "White_king.h"

White_king::White_king():
    king{Game::radius},
    throne{sf::Vector2f(
        king.getRadius() + 2 * Game::space,
        king.getRadius() + 2 * Game::space
    )}
{
    king.move(
        Game::window_width - 3 * Game::space - Game::radius - Game::line_width,
        Game::window_height / 2 - Game::line_width
    );
    king.setFillColor(sf::Color::White);
    king.setOutlineThickness(Game::line_width);
    king.setOutlineColor(sf::Color::White);

    throne.move(
        king.getPosition().x 
        + king.getRadius() - throne.getSize().x / 2,

        king.getPosition().y 
        + king.getRadius() - throne.getSize().y / 2
    );
    throne.setFillColor(sf::Color::Transparent);
    throne.setOutlineThickness(Game::line_width);
    throne.setOutlineColor(sf::Color::White);
}

// White_king::~White_king()
// {

// }