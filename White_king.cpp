#include "White_king.h"

White_king::White_king():
    king{Parameter::radius},
    throne{sf::Vector2f(
        king.getRadius() + 2 * Parameter::space,
        king.getRadius() + 2 * Parameter::space
    )}
{
    king.move(
        Parameter::window_width - 3 * Parameter::space - Parameter::radius,
        Parameter::window_height / 2
    );
    king.setFillColor(sf::Color::White);
    king.setOutlineThickness(Parameter::line_width);
    king.setOutlineColor(sf::Color::White);

    throne.move(
        king.getPosition().x 
        + king.getRadius() - throne.getSize().x / 2,

        king.getPosition().y 
        + king.getRadius() - throne.getSize().y / 2
    );
    throne.setFillColor(sf::Color::Transparent);
    throne.setOutlineThickness(Parameter::line_width);
    throne.setOutlineColor(sf::Color::White);
}

// White_king::~White_king()
// {

// }