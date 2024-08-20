#ifndef PARAMETER_H
#define PARAMETER_H
#pragma once

#include <SFML/Graphics.hpp>

class Parameter
{
public:
    static constexpr unsigned int window_width{1900};
    static constexpr unsigned int window_height{950};
    static constexpr float space{20.f};
    static constexpr float line_width{2.f};
    static constexpr float radius{5.f};
    static sf::Color window_color()
    {
        return sf::Color(17, 17, 17, 255);
    };
private:
};

#endif