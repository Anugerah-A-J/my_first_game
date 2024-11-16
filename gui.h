#include <string>
#include <vector>
#include "geometry.h"
#include "param.h"
#pragma once

class Text
{
public:
    Text(const ALLEGRO_FONT* font, const Vector& origin, const std::string& value):
        font_{font},
        origin_{origin},
        value_{value}
    {}
    
    void draw() const { al_draw_text(
        font_,
        param::default_theme.text_color_,
        origin_.x(),
        origin_.y(),
        ALLEGRO_ALIGN_LEFT,
        &value_.front()
    ); }
private:
    const ALLEGRO_FONT* font_;
    Vector origin_;
    std::string value_;
};

class Button
{
public:
    Button(const ALLEGRO_FONT* font, const Vector& origin, const std::string& text)
    :
        text_{font, origin, text},
        shape_{
            origin,
            Vector(
                al_get_text_width(font, &text.front()) + 2 * al_get_font_line_height(font),
                al_get_font_line_height(font)
            ),
            param::default_theme.background_color_3_,
            0
        }
    {}

    void draw() const
    {
        text_.draw();
        shape_.draw();
    }

    bool contain(const Vector& point) const { return shape_.contain(point); }

    void add_width_by(float how_much) { shape_.add_size_by(Vector(how_much, 0)); }
private:
    Text text_;
    Rectangle shape_;
};

enum class Buttons_arrangement { vertical, horizontal };

class Dialog_box
{
public:
    Dialog_box(const ALLEGRO_FONT* font, const Vector& origin, const Buttons_arrangement& buttons_arrangement)
    :
        buttons_arrangement_{buttons_arrangement},
        shape_{param::default_theme.background_color_2_}
    {}

    void add_message(const Text& text_line)
    {}

    void add_button(const Button& button)
    {
        switch (buttons_arrangement_)
        {
        case Buttons_arrangement::horizontal:
            /* code */
            break;
        
        default:
            break;
        }
    }

    void draw() const
    {
        shape_.draw();
        
        for (const Text& message : messages_)
            message.draw();
        
        for (const Button& button : buttons_)
            button.draw();
    }
private:
    float button_width_sum() const {}
    float max_button_width() const {}
    float max_message_width() const {}

    std::vector<Button> buttons_;
    std::vector<Text> messages_;
    Rectangle shape_;
    Buttons_arrangement buttons_arrangement_;
};