#include <string>
#include <vector>
#include "param.h"
#include <algorithm>
#include "geometry.h"
#pragma once

class One_line_text
{
public:
    static void font(const ALLEGRO_FONT* font) { font_ = font; }
    static float font_height() { return al_get_font_line_height(font_); }

    One_line_text(
        const Vector& origin,
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.text_color_,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color_
    ):
        text_{text}, // no validation for \n
        text_color_{text_color},
        shape_{
            origin,
            Vector(
                al_get_text_width(font_, &text.front()),
                al_get_font_line_height(font_)
            ),
            background_color,
            0
        }
    {}

    void draw() const
    {
        al_draw_text(
            font_,
            text_color_,
            shape_.origin().x(),
            shape_.origin().y(),
            ALLEGRO_ALIGN_LEFT,
            &text_.front()
        );
        shape_.draw();
    }

    bool contain(const Vector& point) const { return shape_.contain(point); }

    float width() const { return shape_.width(); }
    float height() const { return shape_.height(); }

    const std::string& text() const { return text_; }

    // void translate(const Vector& how_far) { origin_ += how_far; }
private:
    std::string text_;
    static const ALLEGRO_FONT* font_;
    ALLEGRO_COLOR text_color_;
    Rectangle shape_;
};

class Dialog_box
{
public:
    Dialog_box(
        const Vector& origin,
        const ALLEGRO_COLOR& color = param::default_theme.background_color_
    ):
        shape_{origin, One_line_text::font_height(), color}
    {}

    void add_message(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.text_color_,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color_)
    {
        messages_.emplace_back(One_line_text(
            message_origin(),
            text,
            text_color,
            background_color));

        update_width();
        update_height();
    }

    void add_choice(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.text_color_,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color_)
    {
        choices_.emplace_back(One_line_text(
            choice_origin(),
            text,
            text_color,
            background_color));

        update_width();
        update_height();
    }

    void draw() const
    {
        shape_.draw();
        
        for (const One_line_text& message : messages_)
            message.draw();
        
        for (const One_line_text& choice : choices_)
            choice.draw();
    }
private:
    float max_choice_width() const
    {
        const One_line_text& choice_with_max_width = *std::max_element(
            choices_.begin(), choices_.end(), [](const One_line_text& choice_1, const One_line_text& choice_2)
        {
            return choice_1.width() < choice_2.width();
        });

        return choice_with_max_width.width() + choice_with_max_width.height();
    }
    
    float sum_message_width() const
    {
        float sum = 0;

        for (const One_line_text& message : messages_)
            sum += message.width();

        return sum;

        // std::string one_line_message;
        // float max_message_width = 0;

        // for (const One_line_text& message : messages_)
        // {
        //     if (message.text().back() != '\n')
        //     {
        //         one_line_message += message.text();
        //     }
        //     else
        //     {
        //         if (one_line_message.length() > max_message_width)
        //             max_message_width = one_line_message.length();
                
        //         one_line_message = "";
        //     }
        // }

        // return max_message_width;
    }

    void update_width() { shape_.width(std::max(sum_message_width(), max_choice_width())); }
    void update_height() { shape_.height((1 + choices_.size()) * One_line_text::font_height()); }

    const Vector& message_origin() const { return shape_.origin() + Vector(
        sum_message_width(),
        0); }
    const Vector& choice_origin() const { return shape_.origin() + Vector(
        0,
        (1 + choices_.size()) * One_line_text::font_height()); }

    Rectangle shape_;
    std::vector<One_line_text> messages_;
    std::vector<One_line_text> choices_;
};