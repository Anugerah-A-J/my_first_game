#include <string>
#include <vector>
#include "param.h"
#include <algorithm>
#include "geometry.h"
#pragma once

class Text
{
public:
    Text(
        const Vector& origin,
        const std::string& text,
        const ALLEGRO_FONT* font,
        const ALLEGRO_COLOR& color = param::gray
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

class Button
{
public:
    Button(
        const Vector& origin,
        const std::string& text,
        const ALLEGRO_FONT* font,
        const ALLEGRO_COLOR& text_color = param::default_theme.text_color_,
        const ALLEGRO_COLOR& button_color = param::default_theme.button_color_
    ):
        text_{
            origin + Vector(al_get_text_width(font, &text.front()) / text.size(), al_get_font_line_height(font)) / 2,
            text,
            font,
            text_color
        },
        shape_{
            origin,
            Vector(
                al_get_text_width(font, &text.front()) * (1 + 1 / text.size()),
                al_get_font_line_height(font) * 2
            ),
            button_color,
            0
        }
    {}

    void draw() const
    {
        text_.draw();
        shape_.draw();
    }

    bool contain(const Vector& point) const { return shape_.contain(point); }

    float width() const { return shape_.width(); }

    void width(float val)
    {
        if (val > shape_.width())
            text_.translate(Vector(val - shape_.width() / 2, 0));

        shape_.width(val);
    }
private:
    Text text_;
    Rectangle shape_;
};

enum class Buttons_arrangement { vertical, horizontal };

class Dialog_box
{
public:
    Dialog_box(
        const Vector& origin,
        const Buttons_arrangement& buttons_arrangement,
        const ALLEGRO_COLOR& color = param::default_theme.background_color_
    ):
        buttons_arrangement_{buttons_arrangement},
        shape_{origin, color}
    {}

    void add_message(
        const Text& val,
        const ALLEGRO_FONT* font,
        const ALLEGRO_COLOR& color = param::default_theme.text_color_
    ){
        messages_.emplace_back(Text(message_origin(), val, font, color));
        update_width();
        update_height();
    }

    void add_button(const Button& button)
    {
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
    float button_width_sum() const
    {
        float sum = 0;

        for (const Button& button : buttons_)
            sum += button.width();

        return sum;
    }

    float max_button_width() const
    {
        const Button& button_with_max_width = *std::max_element(buttons_.begin(), buttons_.end(), [](const Button& button_1, const Button& button_2)
        {
            return button_1.width() < button_2.width();
        });

        return button_with_max_width.width();
    }
    
    float max_message_width() const
    {
        std::string one_line_message;
        float max_message_width = 0;

        for (const Text& message : messages_)
        {
            if (message.text().back() != '\n')
            {
                one_line_message += message.text();
            }
            else
            {
                if (one_line_message.length() > max_message_width)
                    max_message_width = one_line_message.length();
                
                one_line_message = "";
            }
        }

        return max_message_width;
    }

    void buttons_width(float val)
    {
        for (Button& button : buttons_)
            button.width(val);
    }

    void update_width()
    {
        if (buttons_arrangement_ == Buttons_arrangement::horizontal)
        {
            if (max_message_width() > max_button_width() * buttons_.size())
            {
                shape_.width(max_message_width());
                buttons_width(max_message_width() / buttons_.size());
            }
            else
            {
                shape_.width(max_message_width() * buttons_.size());
                buttons_width(max_message_width());
            }
        }
        else
        {
            float width = std::max(max_message_width(), max_button_width());

            shape_.width(width);
            buttons_width(width);
        }
    }

    const Vector& message_origin() const
    {}

    std::vector<Button> buttons_;
    std::vector<Text> messages_;
    Rectangle shape_;
    Buttons_arrangement buttons_arrangement_;
};