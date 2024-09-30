#include <allegro5/color.h>
#pragma once

class Parameter
{
public:
    static unsigned int window_width() { return 1900; }

    static unsigned int window_height() { return 950; }
    
    static float space() { return 20; }
    
    static float line_width() { return 2; }
    
    static float radius() { return 7; }

    static float reach_radius() { return 300; }
    
    static float triangle_height() { return 10; }
    
    static unsigned int move_step() { return 10; }

    static ALLEGRO_COLOR black()
    {
        return al_map_rgb_f(0.1f, 0.1f, 0.1f);
    }
    static ALLEGRO_COLOR red()
    {
        return al_map_rgb_f(0.9f, 0.1f, 0.1f);
    }
    static ALLEGRO_COLOR yellow()
    {
        return al_map_rgb_f(0.9f, 0.9f, 0.1f);
    }
    static ALLEGRO_COLOR green()
    {
        return al_map_rgb_f(0.1f, 0.9f, 0.1f);
    }
    static ALLEGRO_COLOR cyan()
    {
        return al_map_rgb_f(0.1f, 0.9f, 0.9f);
    }
    static ALLEGRO_COLOR blue()
    {
        return al_map_rgb_f(0.1f, 0.1f, 0.9f);
    }
    static ALLEGRO_COLOR magenta()
    {
        return al_map_rgb_f(0.9f, 0.1f, 0.9f);
    }
    static ALLEGRO_COLOR white()
    {
        return al_map_rgb_f(0.9f, 0.9f, 0.9f);
    }
    
    static float sqrt_2() { return 1.41421356237309504880f; }

    static float sqrt_3() { return 1.73205080756887729352f; }
    
    static float pi() { return 3.14159265358979323846f; }
    
    static float sin_15() { return (sqrt_3() - 1) * sqrt_2() / 4; }
    
    static float sin_45() { return sqrt_2() / 2; }
    
    static float sin_75() { return (sqrt_3() + 1) * sqrt_2() / 4; }

    static float delta() { return 0.1f; }
};