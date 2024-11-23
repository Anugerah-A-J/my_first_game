#include <allegro5/color.h>
#include <allegro5/allegro_font.h>
#pragma once

namespace param
{
    class Theme
    {
    public:
        Theme(
            const ALLEGRO_COLOR& passive_text_color,
            const ALLEGRO_COLOR& active_text_color,
            const ALLEGRO_COLOR& background_color
        ):
            passive_text_color_{passive_text_color},
            active_text_color_{active_text_color},
            background_color_{background_color}
        {}

        const ALLEGRO_COLOR passive_text_color_;
        const ALLEGRO_COLOR active_text_color_;
        const ALLEGRO_COLOR background_color_;
    };

    static const int window_width      = 500;
    static const int window_height     = 500;
    static const float unit_length     = 10;
    static const float line_width      = 1;
    static const float reach_radius    = window_height / 4;
    static const int life              = 3;
    static const int translation_step  = 10;

    // static float delta() { return 0.1f;

    static const ALLEGRO_COLOR black   = al_map_rgba_f(0.1f, 0.1f, 0.1f, 1);
    static const ALLEGRO_COLOR red     = al_map_rgba_f(0.9f, 0.1f, 0.1f, 1);
    static const ALLEGRO_COLOR yellow  = al_map_rgba_f(0.9f, 0.9f, 0.1f, 1);
    static const ALLEGRO_COLOR green   = al_map_rgba_f(0.1f, 0.9f, 0.1f, 1);
    static const ALLEGRO_COLOR cyan    = al_map_rgba_f(0.1f, 0.9f, 0.9f, 1);
    static const ALLEGRO_COLOR blue    = al_map_rgba_f(0.1f, 0.1f, 0.9f, 1);
    static const ALLEGRO_COLOR magenta = al_map_rgba_f(0.9f, 0.1f, 0.9f, 1);
    static const ALLEGRO_COLOR white   = al_map_rgba_f(0.9f, 0.9f, 0.9f, 1);
    static const ALLEGRO_COLOR vanish  = al_map_rgba_f(0.1f, 0.1f, 0.1f, 0);
    static const ALLEGRO_COLOR gray    = al_map_rgba_f(0.5f, 0.5f, 0.5f, 0);

    static const float color_transformation_ratio = 0.5f;

    static const float sqrt_2 = 1.41421356237309504880f;
    static const float sqrt_3 = 1.73205080756887729352f;
    static const float pi     = 3.14159265358979323846f;
    static const float sin_15 = (sqrt_3 - 1) * sqrt_2 / 4;
    static const float sin_45 = sqrt_2 / 2;
    static const float sin_75 = (sqrt_3 + 1) * sqrt_2 / 4;

    static const Theme default_theme = Theme(
        al_map_rgba_f(0.6f, 0.6f, 0.6f, 1),
        al_map_rgba_f(0.8f, 0.8f, 0.8f, 1),
        al_map_rgba_f(0.2f, 0.2f, 0.2f, 1)
    );
};