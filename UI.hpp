#include "Shape.hpp"
#include "Param.hpp"
#include <string>
#include <vector>
#include <allegro5/allegro_font.h>
#pragma once

class One_line_text
{
public:
    One_line_text(const Vector& origin, const std::string& text, const ALLEGRO_FONT *const font, const ALLEGRO_COLOR& text_color);
    void Draw() const;
    bool Contain(const Vector& point) const;
    float Width() const;
    const std::string& Text() const;
    void Make_active();
    void Make_passive();
    const Vector& Origin() const;
    void Translate(const Vector& displacement);
private:
    std::string text;
    const ALLEGRO_FONT *const font;
    ALLEGRO_COLOR text_color;
    Rectangle shape;
};

class Dialog_box
{
public:
    void Update_selected_choice(int allegro_keyboard_event_keycode);
    void Update_selected_choice(const Vector& mouse_coordinate);
    void Hide();
    void Show();
    void Draw() const;
    int Selected_choice_index() const;
    void Add_message(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = Param::default_theme.passive_text_color);
    void Erase_message();
protected:
    Dialog_box(
        const Vector& center,
        const ALLEGRO_FONT* const monospaced_font,
        const ALLEGRO_COLOR& color = Param::default_theme.background_color,
        const ALLEGRO_COLOR& line_color = Param::default_theme.line_color);
    void Add_choice(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = Param::default_theme.passive_text_color);
private:
    float Messages_width() const;
    Vector Message_origin() const;
    void Update_messages_origin();
    void Update_choices_origin();
    Vector Choice_origin() const;

    bool visible;
    const Vector center;
    const ALLEGRO_FONT *const monospaced_font;
    int monospaced_font_height;
    int monospaced_font_width;
    Rectangle shape;
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR line_color;
    float line_width;
    std::vector<One_line_text> messages;
    std::vector<One_line_text> choices;
    unsigned int selected_choice_index;
};

class End_dialog_box : public Dialog_box
{
public:
    End_dialog_box(const ALLEGRO_FONT *const font);
};
