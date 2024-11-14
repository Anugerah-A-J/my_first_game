#include <string>
#include <vector>
#include "geometry.h"
#include <allegro5/allegro_font.h>
#pragma once

class Text
{
public:
    Text(ALLEGRO_FONT* font, const ALLEGRO_COLOR& color, const Vector& position, const std::string& value):
        font_{font},
        color_{color},
        position_{position},
        value_{value}
    {}
    
    void draw() const { al_draw_text(
        font_,
        color_,
        position_.x(),
        position_.y(),
        ALLEGRO_ALIGN_LEFT,
        &value_.front()
    ); }
private:
    ALLEGRO_FONT* font_;
    ALLEGRO_COLOR color_;
    Vector position_;
    std::string value_;
};

class Button
{
public:
    void draw() const
    {
        text_.draw();
        shape_.draw();
    }
private:
    Text text_;
    Rectangle shape_;
};

class Pop_up
{
public:
    void draw() const
    {
        shape_.draw();
        message_.draw();
        
        for (const Button& button : buttons_)
            button.draw();
    }
private:
    Rectangle shape_;
    Text message_;
    std::vector<Button> buttons_;
};