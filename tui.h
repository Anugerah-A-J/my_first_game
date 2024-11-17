#include <string>
// #include <vector>
#include "param.h"
// #include <algorithm>
#include "geometry.h"
#pragma once

class Text
{
public:
    Text(
        const Vector& origin,
        const std::string& text,
        const ALLEGRO_FONT* font,
        const ALLEGRO_COLOR& color = param::default_theme.text_color_
    ):
        origin_{origin},
        text_{text},
        font_{font},
        color_{color}
    {}
    
    void draw() const { al_draw_text(
        font_,
        color_,
        origin_.x(),
        origin_.y(),
        ALLEGRO_ALIGN_LEFT,
        &text_.front()
    ); }

    const std::string& text() const { return text_; }

    void translate(const Vector& how_far) { origin_ += how_far; }
private:
    Vector origin_;
    std::string text_;
    const ALLEGRO_FONT* font_;
    ALLEGRO_COLOR color_;
};