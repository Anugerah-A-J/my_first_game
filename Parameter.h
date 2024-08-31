#include <allegro5/allegro5.h>

#ifndef PARAMETER_H
#define PARAMETER_H
#pragma once

class Parameter
{
public:
    static constexpr unsigned int window_width {1900};
    static constexpr unsigned int window_height {950};
    static constexpr float space {20.f};
    static constexpr float line_width {2.f};
    static constexpr float radius {7.f};
    static constexpr float reach_radius {300.f};
    static constexpr float triangle_height {10.f};
    static constexpr unsigned int move_step {10};

    static ALLEGRO_COLOR window_color()
    {
        return al_map_rgba_f(0.1, 0.1, 0.1, 1);
    };
    
    static constexpr float sqrt_2 {1.41421356237309504880};
    static constexpr float sqrt_3 {1.73205080756887729352};
    static constexpr float pi     {3.14159265358979323846};
    static constexpr float sin_15 {(sqrt_3 - 1) * sqrt_2 / 4};
    static constexpr float sin_45 {sqrt_2 / 2};
    static constexpr float sin_75 {(sqrt_3 + 1) * sqrt_2 / 4};
};

#endif