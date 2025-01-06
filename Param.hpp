#include <allegro5/color.h>
#pragma once

class Theme
{
    friend class Param;
public:
    const ALLEGRO_COLOR passive_text_color;
    const ALLEGRO_COLOR active_text_color;
    const ALLEGRO_COLOR background_color;
    const ALLEGRO_COLOR line_color;
private:
    Theme(
        const ALLEGRO_COLOR& passive_text_color,
        const ALLEGRO_COLOR& active_text_color,
        const ALLEGRO_COLOR& background_color,
        const ALLEGRO_COLOR& line_color
    ):
        passive_text_color{passive_text_color},
        active_text_color{active_text_color},
        background_color{background_color},
        line_color{line_color}
    {}
};

class Param
{
public:
    static constexpr float unit_length = 10;
    static constexpr int translation_step = 10;
    static constexpr float reach_radius = 300;
    static constexpr float line_width = 1;
    // static constexpr float reach_radius    = window_height;
    static constexpr int life = 3;
    // static constexpr int life              = 1;
    static constexpr int window_width = 1000;
    static constexpr int window_height = 800;

    // static float delta() { return 0.1f;

    inline static const ALLEGRO_COLOR black = al_map_rgba_f(0.1f, 0.1f, 0.1f, 1);
    inline static const ALLEGRO_COLOR red = al_map_rgba_f(0.9f, 0.1f, 0.1f, 1);
    inline static const ALLEGRO_COLOR yellow = al_map_rgba_f(0.9f, 0.9f, 0.1f, 1);
    inline static const ALLEGRO_COLOR green = al_map_rgba_f(0.1f, 0.9f, 0.1f, 1);
    inline static const ALLEGRO_COLOR cyan = al_map_rgba_f(0.1f, 0.9f, 0.9f, 1);
    inline static const ALLEGRO_COLOR blue = al_map_rgba_f(0.1f, 0.1f, 0.9f, 1);
    inline static const ALLEGRO_COLOR magenta = al_map_rgba_f(0.9f, 0.1f, 0.9f, 1);
    inline static const ALLEGRO_COLOR white = al_map_rgba_f(0.9f, 0.9f, 0.9f, 1);
    inline static const ALLEGRO_COLOR vanish = al_map_rgba_f(0.1f, 0.1f, 0.1f, 0);
    inline static const ALLEGRO_COLOR gray = al_map_rgba_f(0.5f, 0.5f, 0.5f, 0);

    static constexpr float color_transformation_ratio = 0.5f;

    static constexpr float sqrt_2 = 1.41421356237309504880f;
    static constexpr float sqrt_3 = 1.73205080756887729352f;
    static constexpr float pi = 3.14159265358979323846f;
    static constexpr float sin_15 = (sqrt_3 - 1) * sqrt_2 / 4;
    static constexpr float sin_45 = sqrt_2 / 2;
    static constexpr float sin_75 = (sqrt_3 + 1) * sqrt_2 / 4;

    inline static const Theme default_theme = Theme(
        Param::gray,
        Param::white,
        al_map_rgba_f(0.2f, 0.2f, 0.2f, 1),
        Param::gray
    );
};
