#include "UI.hpp"
#include <algorithm>

One_line_text::One_line_text( const Vector& origin, const std::string& text, const ALLEGRO_FONT* const font, const ALLEGRO_COLOR& text_color)
:
    text{text}, // no validation for \n
    font{font},
    text_color{text_color},
    shape{origin,Vector(al_get_text_width(font, &text.front()), al_get_font_line_height(font))}
{}

void One_line_text::Draw() const
{
    al_draw_text(font, text_color, shape.Origin().X(), shape.Origin().Y(), ALLEGRO_ALIGN_LEFT, &text.front());
}

bool One_line_text::Contain(const Vector& point) const
{
    return shape.Contain(point);
}

float One_line_text::Width() const
{
    return shape.Width();
}

const std::string& One_line_text::Text() const
{
    return text;
}

void One_line_text::Make_active()
{
    text_color = Param::default_theme.active_text_color;
}

void One_line_text::Make_passive()
{
    text_color = Param::default_theme.passive_text_color;
}

const Vector& One_line_text::Origin() const
{
    return shape.Origin();
}

void One_line_text::Translate(const Vector& displacement)
{
    shape.Translate(displacement);
}

void Dialog_box::Update_selected_choice(int allegro_keyboard_event_keycode)
{
    if (allegro_keyboard_event_keycode != ALLEGRO_KEY_DOWN
        && allegro_keyboard_event_keycode != ALLEGRO_KEY_UP)
        return;

    choices.at(selected_choice_index).Make_passive();

    if (allegro_keyboard_event_keycode == ALLEGRO_KEY_DOWN
        && selected_choice_index != choices.size() - 1)
        selected_choice_index++;

    else if (allegro_keyboard_event_keycode == ALLEGRO_KEY_DOWN
                && selected_choice_index == choices.size() - 1)
        selected_choice_index = 0;

    if (allegro_keyboard_event_keycode == ALLEGRO_KEY_UP && selected_choice_index != 0)
        selected_choice_index--;

    else if (allegro_keyboard_event_keycode == ALLEGRO_KEY_UP && selected_choice_index == 0)
        selected_choice_index = choices.size() - 1;

    choices.at(selected_choice_index).Make_active();
}

void Dialog_box::Update_selected_choice(const Vector& mouse_coordinate)
{
    std::vector<One_line_text>::iterator selected_choice_iterator
        = find_if(choices.begin(), choices.end(), [&](const One_line_text& choice) {
                return choice.Contain(mouse_coordinate);
            });

    if (selected_choice_iterator != choices.end()
        && selected_choice_iterator - choices.begin() != selected_choice_index)
    {
        choices.at(selected_choice_index).Make_passive();
        selected_choice_index = selected_choice_iterator - choices.begin();
        choices.at(selected_choice_index).Make_active();
    }
}

void Dialog_box::Draw() const
{
    if (!visible)
        return;
        
    shape.Draw(color);
    shape.Draw(line_color, line_width);

    for (const One_line_text& message : messages)
        message.Draw();

    for (const One_line_text& choice : choices)
        choice.Draw();
}

int Dialog_box::Selected_choice_index() const { return selected_choice_index; }

void Dialog_box::Add_message(
    const std::string& text,
    const ALLEGRO_COLOR& text_color = Param::default_theme.passive_text_color,
    const ALLEGRO_COLOR& background_color = Param::default_theme.background_color)
{
    if (Messages_width() + (text.length() + 1) * monospaced_font_width > shape.Width())
        shape.Width(Messages_width() + (text.length() + 1) * monospaced_font_width);

    shape.Origin(center - shape.Size() * 0.5f);

    Update_messages_origin();

    messages.emplace_back(Message_origin(), text, monospaced_font, text_color);
}

void Dialog_box::Erase_message()
{
    messages.clear();
}

Dialog_box::Dialog_box(
    const Vector& center,
    const ALLEGRO_FONT* const monospaced_font,
    const ALLEGRO_COLOR& color = Param::default_theme.background_color,
    const ALLEGRO_COLOR& line_color = Param::default_theme.line_color)
:
    visible{false},
    center{center},
    monospaced_font{monospaced_font},
    monospaced_font_height{al_get_font_line_height(monospaced_font)},
    monospaced_font_width{al_get_text_width(monospaced_font, "a")},
    shape{
        center - Vector(0, monospaced_font_height),
        Vector(0, 2 * monospaced_font_height),
    },
    color{color},
    line_color{line_color},
    line_width{Param::line_width},
    selected_choice_index{0}
{}

void Dialog_box::Add_choice(
    const std::string& text,
    const ALLEGRO_COLOR& text_color = Param::default_theme.passive_text_color,
    const ALLEGRO_COLOR& background_color = Param::default_theme.background_color)
{
    if ((text.length() + 1) * monospaced_font_width > shape.Width())
        shape.Width((text.length() + 1) * monospaced_font_width);

    shape.Height(shape.Height() + 1.5 * monospaced_font_height);

    shape.Origin(center - shape.Size() * 0.5);

    Update_choices_origin();

    choices.emplace_back(Choice_origin(), text, monospaced_font, text_color);

    if (choices.size() == 1)
        choices.front().Make_active();
}

float Dialog_box::Messages_width() const
{
    float sum = 0;

    for (const One_line_text& message : messages)
        sum += message.Width();

    return sum;
}

Vector Dialog_box::Message_origin() const
{
    return shape.Origin()
            + Vector(Messages_width() + monospaced_font_width * 0.5f,
                    monospaced_font_height * 0.5f);
}

void Dialog_box::Update_messages_origin()
{
    if (messages.empty())
        return;

    Vector displacement = shape.Origin() - messages.front().Origin();

    std::for_each(messages.begin(), messages.end(), [&](One_line_text& message) {
        message.Translate(displacement);
    });
}

void Dialog_box::Update_choices_origin()
{
    if (choices.empty())
        return;

    Vector displacement = shape.Origin()
                            + Vector(monospaced_font_width * 0.5f, monospaced_font_height * 2)
                            - choices.front().Origin();

    std::for_each(choices.begin(), choices.end(), [&](One_line_text& choice) {
        choice.Translate(displacement);
    });
}

Vector Dialog_box::Choice_origin() const
{
    return shape.Origin()
            + Vector(monospaced_font_width * 0.5f,
                    (2 + choices.size() * 1.5) * monospaced_font_height);
}

End_dialog_box::End_dialog_box(const ALLEGRO_FONT *const font)
    : Dialog_box{Vector(Param::window_width / 2, Param::window_height / 2), font}
{
    Add_choice("> Play again");
    Add_choice("> Quit");
}