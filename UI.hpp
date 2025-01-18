#include "Shape.hpp"
#include "Param.hpp"
#include <string>
#include <vector>
#include <allegro5/allegro_font.h>
#pragma once

class One_line_text_centered
{
public:
    One_line_text_centered(const Vector& position, const std::string& text, const ALLEGRO_FONT *const font, const ALLEGRO_COLOR& text_color);
    void Draw() const;
    bool Contain(const Vector& point) const;
    float Width() const;
    float Height() const;
    const std::string& Text() const;
    void Make_active();
    void Make_passive();
    Vector Position() const;
    void Translate(const Vector& displacement);
    void Set(const std::string& text, const ALLEGRO_COLOR& text_color);
protected:
    std::string text;
    const ALLEGRO_FONT *const font;
    ALLEGRO_COLOR text_color;
    Rectangle shape;
};

class Dialog_box
{
public:
    // void Update_selected_choice(int allegro_keyboard_event_keycode);
    // void Update_selected_choice(const Vector& mouse_coordinate);
    int Selected_choice_index(const Vector& mouse_coordinate, bool mouse_is_left_clicked);
    void Hide();
    void Show();
    void Draw() const;
    void Set_message(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = Param::default_theme.passive_text_color);
protected:
    Dialog_box(
        const Vector& center,
        const ALLEGRO_FONT* const font,
        const ALLEGRO_COLOR& color = Param::default_theme.background_color,
        const ALLEGRO_COLOR& line_color = Param::default_theme.line_color);
    void Add_choice(
        const std::string& text,
        const ALLEGRO_COLOR& text_color = Param::default_theme.passive_text_color);
private:
    Vector Message_position() const;
    void Update_message_and_choice_position();
    Vector Choice_position() const;
    float Choice_height() const;

    bool visible;
    const Vector center;
    const ALLEGRO_FONT *const font;
    Rectangle shape;
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR line_color;
    float line_width;
    One_line_text_centered message;
    std::vector<One_line_text_centered> choice;
    int selected_choice_index;
};

class End_dialog_box : public Dialog_box
{
public:
    End_dialog_box(const ALLEGRO_FONT *const font);
};
