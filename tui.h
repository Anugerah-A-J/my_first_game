#include <string>
#include <vector>
#include "param.h"
#include <algorithm>
#include "geometry.h"
#pragma once

class One_line_text
{
public:
    static void Font(const ALLEGRO_FONT* font) { font = font; }
    static float Font_height() { return al_get_font_line_height(font); }
    // static float font_width() { return al_get_font_line_height(font_); }

    One_line_text(
        const Vector& origin,
        const std::string& text,
        const ALLEGRO_COLOR& text_color,
        const ALLEGRO_COLOR& background_color
    ):
        text{text}, // no validation for \n
        text_color{text_color},
        shape{
            origin,
            Vector(
                al_get_text_width(font, &text.front()),
                al_get_font_line_height(font)
            ),
            background_color,
            0
        }
    {}

    void Draw() const
    {
        al_draw_text(
            font,
            text_color,
            shape.Origin().X(),
            shape.Origin().Y(),
            ALLEGRO_ALIGN_LEFT,
            &text.front()
        );
        shape.Draw();
    }

    bool Contain(const Vector& point) const { return shape.Contain(point); }

    float Width() const { return shape.Width(); }

    const std::string& Text() const { return text; }

    void Make_active() { text_color = param::default_theme.active_text_color; }
    void Make_pasive() { text_color = param::default_theme.passive_text_color; }
private:
    std::string text;
    inline static const ALLEGRO_FONT* font;
    ALLEGRO_COLOR text_color;
    Rectangle shape;
};

class Dialog_box
{
public:
    void Update_selected_choice(int allegro_keyboard_event_keycode)
    {
        ;
    }

    void Update_selected_choice(const Vector& mouse_coordinate)
    {
        auto selected_choice_iterator = find_if(choices.begin(), choices.end(), [](){});

        if (selected_choice_iterator != choices.end() && &*selected_choice_iterator != selected_choice)
        {
            selected_choice->Make_pasive();
            selected_choice = &*selected_choice_iterator;
            selected_choice->Make_active();
        }
    }

    void Draw() const
    {
        shape.Draw();
        
        for (const One_line_text& message : messages)
            message.Draw();
        
        for (const One_line_text& choice : choices)
            choice.Draw();
    }
protected:
    Dialog_box(
        const Vector& center,
        const ALLEGRO_COLOR& color = param::default_theme.background_color
    ):
        center{center},
        shape{
            center - Vector(0, One_line_text::Font_height()),
            One_line_text::Font_height(),
            color
        }
    {}

    void Add_message(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.passive_text_color,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color)
    {
        messages.emplace_back(One_line_text(
            Message_origin(),
            text,
            text_color,
            background_color));

        if (Messages_width() > shape.Width())
            shape.Width(Messages_width());

        shape.Origin(center - shape.Size());
    }

    void Add_choice(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = param::default_theme.passive_text_color,
        const ALLEGRO_COLOR& background_color = param::default_theme.background_color)
    {
        choices.emplace_back(One_line_text(
            Choice_origin(),
            text,
            text_color,
            background_color));

        if (choices.size() == 1)
            selected_choice = &choices.front();

        if (choices.back().Width() > shape.Width())
            shape.Width(choices.back().Width());

        shape.Height(shape.Height() + One_line_text::Font_height());

        shape.Origin(center - shape.Size());
    }
private:
    float Messages_width() const
    {
        float sum = 0;

        for (const One_line_text& message : messages)
            sum += message.Width();

        return sum;
    }

    Vector Message_origin() const
    {
        return shape.Origin() + Vector(Messages_width(), 0);
    }

    Vector Choice_origin() const
    {
        return shape.Origin() + Vector(0, (1 + choices.size()) * One_line_text::Font_height());
    }

    const Vector center;
    Rectangle shape;
    std::vector<One_line_text> messages;
    std::vector<One_line_text> choices;
    One_line_text* selected_choice;
};