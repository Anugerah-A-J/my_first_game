#include "Black_king.h"

Black_king::Black_king():
    king{},
    throne{},
    king{Parameter::radius},
    throne{sf::Vector2f(
        king.getRadius() + 2 * Parameter::space,
        king.getRadius() + 2 * Parameter::space
    )}
{
    king.move(
        2 * Parameter::space - king.getRadius() - Parameter::line_width / 2,
        Parameter::space - king.getRadius() - Parameter::line_width / 2
    );
    // king.move(
    //     Parameter::space + king.getRadius(),
    //     Parameter::window_height / 2 - Parameter::space
    // );
    king.setFillColor(sf::Color::Transparent);
    king.setOutlineThickness(Parameter::line_width);
    king.setOutlineColor(sf::Color::White);

    throne.move(king.getPosition());
    throne.move(king.getRadius(), king.getRadius());
    throne.move(
        throne.getSize().x / -2,
        throne.getSize().y / -2
    );
    throne.setFillColor(sf::Color::Transparent);
    throne.setOutlineThickness(Parameter::line_width);
    throne.setOutlineColor(sf::Color::White);
}

// White_king::~White_king()
// {

// }