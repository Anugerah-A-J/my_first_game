#include "UI.hpp"
#include "Shape.hpp"
#include <algorithm>
#include <allegro5/allegro_font.h>

One_line_text_centered::One_line_text_centered(const Vector& position, const std::string& text, const ALLEGRO_FONT* const font, const ALLEGRO_COLOR& text_color)
:
    text{text}, // no validation for \n
    font{font},
    text_color{text_color},
    shape{
        position - Vector(al_get_text_width(font, &text.front()) / 2.f, 0),
        Vector(al_get_text_width(font, &text.front()), al_get_font_line_height(font))
    }
{}

void One_line_text_centered::Draw() const
{
    shape.Draw(Param::black);
    al_draw_text(font, text_color, Position().x, Position().y, ALLEGRO_ALIGN_CENTER, &text.front());
}

bool One_line_text_centered::Contain(const Vector& point) const
{
    return shape.Contain(point);
}

float One_line_text_centered::Width() const
{
    return shape.Width();
}

float One_line_text_centered::Height() const
{
    return shape.Height();
}

const std::string& One_line_text_centered::Text() const
{
    return text;
}

void One_line_text_centered::Make_active()
{
    text_color = Param::default_theme.active_text_color;
}

void One_line_text_centered::Make_passive()
{
    text_color = Param::default_theme.passive_text_color;
}

Vector One_line_text_centered::Position() const
{
    return shape.Top().Center();
}

void One_line_text_centered::Translate(const Vector& displacement)
{
    shape.Translate(displacement);
}

void One_line_text_centered::Set(const std::string& text, const ALLEGRO_COLOR& text_color)
{
    this->text = text;
    this->text_color = text_color;
    float new_width = al_get_text_width(font, &text.front());
    shape.Width(new_width);
    shape.Translate(Vector(shape.Width() - new_width, 0) / 2.f);
}


// void Dialog_box::Update_selected_choice(int allegro_keyboard_event_keycode)
// {
//     if (allegro_keyboard_event_keycode != ALLEGRO_KEY_DOWN
//         && allegro_keyboard_event_keycode != ALLEGRO_KEY_UP)
//         return;

//     choices.at(selected_choice_index).Make_passive();

//     if (allegro_keyboard_event_keycode == ALLEGRO_KEY_DOWN
//         && selected_choice_index != choices.size() - 1)
//         selected_choice_index++;

//     else if (allegro_keyboard_event_keycode == ALLEGRO_KEY_DOWN
//                 && selected_choice_index == choices.size() - 1)
//         selected_choice_index = 0;

//     if (allegro_keyboard_event_keycode == ALLEGRO_KEY_UP && selected_choice_index != 0)
//         selected_choice_index--;

//     else if (allegro_keyboard_event_keycode == ALLEGRO_KEY_UP && selected_choice_index == 0)
//         selected_choice_index = choices.size() - 1;

//     choices.at(selected_choice_index).Make_active();
// }

// void Dialog_box::Update_selected_choice(const Vector& mouse_coordinate)
// {
//     std::vector<One_line_text>::iterator selected_choice_iterator
//         = find_if(choices.begin(), choices.end(), [&](const One_line_text& choice) {
//                 return choice.Contain(mouse_coordinate);
//             });

//     if (selected_choice_iterator != choices.end()
//         && selected_choice_iterator - choices.begin() != selected_choice_index)
//     {
//         choices.at(selected_choice_index).Make_passive();
//         selected_choice_index = selected_choice_iterator - choices.begin();
//         choices.at(selected_choice_index).Make_active();
//     }
// }

void Dialog_box::Hide()
{
    visible = false;
}

void Dialog_box::Show()
{
    visible = true;
}

void Dialog_box::Draw() const
{
    if (!visible)
        return;
        
    shape.Draw(color);
    shape.Draw(line_color, line_width);

    message.Draw();

    for (const auto& c : choice)
        c.Draw();
}

int Dialog_box::Selected_choice_index(const Vector& mouse_coordinate, bool mouse_is_left_clicked)
{
    auto selected_choice_iterator
        = find_if(choice.begin(), choice.end(), [&](const auto& choice) {
                return choice.Contain(mouse_coordinate);
            });

    if (selected_choice_iterator != choice.end()
        && selected_choice_iterator - choice.begin() != selected_choice_index)
    {
        if (selected_choice_index != -1)
            choice.at(selected_choice_index).Make_passive();
        
        selected_choice_index = selected_choice_iterator - choice.begin();
        
        if (selected_choice_index != -1)
            choice.at(selected_choice_index).Make_active();
    }
    else if (selected_choice_iterator == choice.end() && selected_choice_index != -1)
    {
        choice.at(selected_choice_index).Make_passive();
        selected_choice_index = -1;
    }

    if (mouse_is_left_clicked)
        return selected_choice_index;
    else
        return -1;
}

void Dialog_box::Set_message(const std::string& text, const ALLEGRO_COLOR& text_color)
{
    if (message.Width() + al_get_text_width(font, &text.front()) + Param::unit_length * 2 > shape.Width())
        shape.Width(
            message.Width() + al_get_text_width(font, &text.front()) + Param::unit_length * 2
        );

    shape.origin = center - shape.Size() * 0.5f;

    message.Set(text, text_color);
}

Dialog_box::Dialog_box(
    const Vector& center,
    const ALLEGRO_FONT* const font,
    const ALLEGRO_COLOR& color,
    const ALLEGRO_COLOR& line_color)
:
    visible{true},
    center{center},
    font{font},
    shape{
        center - Vector(0, Param::unit_length),
        Vector(0, Param::unit_length * 2 + al_get_font_line_height(font)),
    },
    color{color},
    line_color{line_color},
    line_width{Param::line_width},
    message{
        shape.Center() - Vector(0, al_get_font_line_height(font) / 2.f),
        "x",
        font,
        line_color
    },
    selected_choice_index{-1}
{}

void Dialog_box::Add_choice(const std::string& text, const ALLEGRO_COLOR& text_color)
{
    if (al_get_text_width(font, &text.front()) + Param::unit_length * 2 > shape.Width())
        shape.Width(
            al_get_text_width(font, &text.front()) + Param::unit_length * 2
        );

    shape.Height(
        shape.Height() + al_get_font_line_height(font) + Param::unit_length
    );

    shape.origin = center - shape.Size() / 2.f;

    Update_message_and_choice_position();

    choice.emplace_back(Choice_position(), text, font, text_color);
}

void Dialog_box::Update_message_and_choice_position()
{
    Vector v = shape.Top().Center() - message.Position() - Vector(0, Param::unit_length);

    message.Translate(v);
    
    if (choice.empty())
        return;

    std::for_each(choice.begin(), choice.end(), [&v](auto& oltc)
    {
        oltc.Translate(v);
    });
}

Vector Dialog_box::Choice_position() const
{
    return shape.Top().Center() + Vector(
        0,
        Param::unit_length +
        message.Height() +
        Param::unit_length * choice.size() +
        Choice_height()
        + Param::unit_length
    );
}

float Dialog_box::Choice_height() const
{
    float sum = 0;

    for (const auto& c : choice)
        sum += c.Height();

    return sum;
} 

End_dialog_box::End_dialog_box(const ALLEGRO_FONT *const font)
    : Dialog_box{Vector(Param::window_width / 2.f, Param::window_height / 2.f), font}
{
    Add_choice("Play again");
    Add_choice("Quit");
}