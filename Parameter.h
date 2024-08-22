#include <allegro5/allegro5.h>

#ifndef PARAMETER_H
#define PARAMETER_H
#pragma once

class Parameter
{
public:
    static constexpr unsigned int window_width{1900};
    static constexpr unsigned int window_height{950};
    static constexpr float space{20.f};
    static constexpr float line_width{2.f};
    static constexpr float radius{5.f};
    static ALLEGRO_COLOR window_color()
    {
        return al_map_rgba_f(0.1, 0.1, 0.1, 1);
    };
private:
};

#endif