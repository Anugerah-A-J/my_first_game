#include <allegro5/color.h>
#pragma once

namespace param
{
    const int window_width      = 1000;
    const int window_height     = window_width / 2;
    const float space           = window_width / 100;
    const float line_width      = window_width / 1000;
    const float radius          = window_width / 200;
    const float reach_radius    = window_width / 8;
    const float triangle_height = window_width / 200;
    const int move_step         = window_width / 200;

    // static float delta() { return 0.1f;

    const ALLEGRO_COLOR black      = al_map_rgba_f(0.1f, 0.1f, 0.1f, 1);
    const ALLEGRO_COLOR red        = al_map_rgba_f(0.9f, 0.1f, 0.1f, 1);
    const ALLEGRO_COLOR yellow     = al_map_rgba_f(0.9f, 0.9f, 0.1f, 1);
    const ALLEGRO_COLOR green      = al_map_rgba_f(0.1f, 0.9f, 0.1f, 1);
    const ALLEGRO_COLOR cyan       = al_map_rgba_f(0.1f, 0.9f, 0.9f, 1);
    const ALLEGRO_COLOR blue       = al_map_rgba_f(0.1f, 0.1f, 0.9f, 1);
    const ALLEGRO_COLOR magenta    = al_map_rgba_f(0.9f, 0.1f, 0.9f, 1);
    const ALLEGRO_COLOR white      = al_map_rgba_f(0.9f, 0.9f, 0.9f, 1);
    const ALLEGRO_COLOR dead_color = al_map_rgba_f(0.1f, 0.1f, 0.1f, 0);

    const float color_transformation_ratio = 0.5f;

    const float sqrt_2 = 1.41421356237309504880f;
    const float sqrt_3 = 1.73205080756887729352f;
    const float pi = 3.14159265358979323846f;
    const float sin_15 = (sqrt_3 - 1) * sqrt_2 / 4;
    const float sin_45 = sqrt_2 / 2;
    const float sin_75 = (sqrt_3 + 1) * sqrt_2 / 4;
}