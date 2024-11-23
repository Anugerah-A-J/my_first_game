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
    // static float font_width() { return al_get_font_line_height(font_); }

    One_line_text(
        const Vector& origin,
        const std::string& text,
        const ALLEGRO_COLOR& text_color,
        const ALLEGRO_COLOR& background_color
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
            shape_.origin().X(),
            shape_.origin().Y(),
            ALLEGRO_ALIGN_LEFT,
            &text_.front()
        );
        shape_.draw();
    }

    bool contain(const Vector& point) const { return shape_.contain(point); }

    float width() const { return shape_.width(); }

    const std::string& text() const { return text_; }

    void make_active() { text_color_ = param::default_theme.active_text_color_; }
    void make_pasive() { text_color_ = param::default_theme.passive_text_color_; }
private:
    std::string text_;
    inline static const ALLEGRO_FONT* font_;
    ALLEGRO_COLOR text_color_;
    Rectangle shape_;
};

class Dialog_box
{
public:
    void update_selected_choice(int allegro_keyboard_event_keycode)
    {
        ;
    }

    void update_selected_choice(const Vector& mouse_coordinate)
    {
        auto selected_choice_iterator = find_if(choices_.begin(), choices_.end(), [](){});

        if (selected_choice_iterator != choices_.end() && &*selected_choice_iterator != selected_choice_)
        {
            selected_choice_->make_pasive();
            selected_choice_ = &*selected_choice_iterator;
            selected_choice_->make_active();
        }
    }
protected:
    Dialog_box(
        const Vector& center,
        const ALLEGRO_COLOR& color = param::default_theme.background_color_
    ):
        center_{center},
        shape_{
            center - Vector(0, One_line_text::font_height()),
            One_line_text::font_height(),
            color
        }
    {}

    void add_message(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.passive_text_color_,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color_)
    {
        messages_.emplace_back(One_line_text(
            message_origin(),
            text,
            text_color,
            background_color));

        if (messages_width() > shape_.width())
            shape_.width(messages_width());

        shape_.origin(center_ - shape_.size());
    }

    void add_choice(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.passive_text_color_,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color_)
    {
        choices_.emplace_back(One_line_text(
            choice_origin(),
            text,
            text_color,
            background_color));

        if (choices_.size() == 1)
            selected_choice_ = &choices_.front();

        if (choices_.back().width() > shape_.width())
            shape_.width(choices_.back().width());

        shape_.height(shape_.height() + One_line_text::font_height());

        shape_.origin(center_ - shape_.size());
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
    float messages_width() const
    {
        float sum = 0;

        for (const One_line_text& message : messages_)
            sum += message.width();

        return sum;
    }

    Vector message_origin() const
    {
        return shape_.origin() + Vector(messages_width(), 0);
    }

    Vector choice_origin() const
    {
        return shape_.origin() + Vector(0, (1 + choices_.size()) * One_line_text::font_height());
    }

    const Vector center_;
    Rectangle shape_;
    std::vector<One_line_text> messages_;
    std::vector<One_line_text> choices_;
    One_line_text* selected_choice_;
};