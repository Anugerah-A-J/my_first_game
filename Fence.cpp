#include "Fence.h"

Fence::Fence():
    sf::RectangleShape{sf::Vector2f(
        Parameter::window_width - 4 * Parameter::space,
        Parameter::window_height - 2 * Parameter::space
    )}
{
    move(2 * Parameter::space, Parameter::space);
    setFillColor(sf::Color::Transparent);
    setOutlineThickness(Parameter::line_width);
    setOutlineColor(sf::Color::Red);
}

// Fence::~Fence()
// {

// }