#include "Game.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory>

Game::Game()
:
    al_init_is_success{al_init()},
    al_init_primitives_addon_is_success{al_init_primitives_addon()},
    al_install_keyboard_is_success{al_install_keyboard()},
    al_install_mouse_is_success{al_install_mouse()},

    timer{al_create_timer(1.0 / 30.0)},
    queue{al_create_event_queue()},
    display{al_create_display(Param::window_width, Param::window_height)},
    // font{al_create_builtin_font()},
    al_init_font_addon_is_success{al_init_font_addon()},
    al_init_ttf_addon_is_success{al_init_ttf_addon()},
    font{al_load_font("font/calibri.ttf", Param::unit_length * 2, ALLEGRO_TTF_NO_AUTOHINT)},

    player_magenta{map_1},
    player_cyan{map_1},

    end_dialog_box{font},

    active_player{&player_magenta},
    passive_player{&player_cyan},
    what_to_do{&aiming},

    mouse_position{0, 0},
    exit{false}
{
    aiming = [this]()
    {
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if (active_player->Contain(mouse_position))
            {
                aim.Center(active_player->Center());
                aim.Show_reach_circle();
            }
            else if (aim.Reach_circle_is_visible() && active_player->Reach(mouse_position))
            {
                aim.Update_direction(mouse_position);
                aim.Show_direction_sign();
            }
            else if (aim.Direction_sign_is_visible())
                aim.Hide();
        }

        if (
            aim.Direction_sign_is_visible() &&
            event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
            event.mouse.button == 1 &&
            active_player->Reach(mouse_position))
        {    
            aim.Hide();
            what_to_do = &moving;
            active_player->Update_translation(aim.End_point());
        }
    };

    moving = [this]()
    {
        if (event.type != ALLEGRO_EVENT_TIMER)
            return;

        Move();
        passive_player->Update_life();
        active_player->Update_life();
        // trail.emplace_back(active_pawns->back().Last_translation());

        if (passive_player->Dead())
        {
            std::string message = passive_player == &player_magenta ? "Cyan Win" : "Magenta Win";
            end_dialog_box.Set_message(message, active_player->Color());
            end_dialog_box.Show();
            what_to_do = &ending;
            return;
        }

        if (active_player->Dead())
        {
            std::string message = active_player == &player_magenta ? "Cyan Win" : "Magenta Win";
            end_dialog_box.Set_message(message, passive_player->Color());
            end_dialog_box.Show();
            what_to_do = &ending;
            return;
        }

        if (active_player->Finish_moving() && passive_player->Finish_moving())
        {

            std::swap(active_player, passive_player);
            aim.Color(active_player->Color());
            what_to_do = &aiming;
        }
    };

    ending = [&]()
    {
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            bool mouse_is_left_clicked = event.mouse.button == 1;

            switch (end_dialog_box.Selected_choice_index(mouse_position, mouse_is_left_clicked))
            {
            case 0:
                aim.Color(Param::magenta);

                player_cyan.Reset_all(map_1);
                player_magenta.Reset_all(map_1);

                active_player = &player_magenta;
                passive_player = &player_cyan;

                what_to_do = &aiming;

                end_dialog_box.Hide();

                break;
            case 1:
                exit = true;
                break;
            }
        }
    };
}

Game::~Game()
{
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void Game::Run()
{
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_start_timer(timer);

    while (true) {
        al_wait_for_event(queue, &event);

        // bool window_is_closed = event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
        // bool esc_is_pressed = event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = true;

        if (exit)
            break;

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
            mouse_position = Vector(event.mouse.x, event.mouse.y);

        (*what_to_do)();

        if (event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue))
            Draw(),
            al_flip_display();
    }
}

void Game::Draw() const
{
    al_clear_to_color(Param::black);

    aim.Draw();

    map_1.Draw();
    
    player_cyan.Draw();
    player_magenta.Draw();
    end_dialog_box.Draw();

    // std::string mx = std::to_string(player_magenta.Center().x);
    // std::string my = std::to_string(player_magenta.Center().y);
    // std::string cx = std::to_string(player_cyan.Center().x);
    // std::string cy = std::to_string(player_cyan.Center().y);
    // std::string max_x = std::to_string(map_1.Fence_shape().Bottom_right().x);
    // std::string max_y = std::to_string(map_1.Fence_shape().Bottom_right().y);
    
    // std::string text_m = "Magenta: " + mx + ", " + my;
    // std::string text_c = "Cyan: " + cx + ", " + cy;
    
    // al_draw_text(font, Param::white, Param::window_width / 2, Param::unit_length, ALLEGRO_ALIGN_CENTER, &text_m.front());
    // al_draw_text(font, Param::white, Param::window_width / 2, Param::unit_length * 2, ALLEGRO_ALIGN_CENTER, &text_c.front());
    // al_draw_text(font, Param::white, std::stof(max_x), std::stof(max_y), ALLEGRO_ALIGN_LEFT, &max_x.front());
    // al_draw_text(font, Param::white, std::stof(max_x), std::stof(max_y) + Param::unit_length, ALLEGRO_ALIGN_LEFT, &max_y.front());
}

void Game::Move()
{
    active_player->Move();
    passive_player->Move();

    if (active_player->Finish_moving() && passive_player->Finish_moving())
        return;

    std::vector<std::shared_ptr<Collision>> collided;
    float earliest = 2;

    constexpr auto update_collided_and_earliest = [](
        std::vector<std::shared_ptr<Collision>>& collided,
        float& earliest,
        std::shared_ptr<Collision> temp)
    {
        if (temp->Get_t() == 2)
            return;

        collided.emplace_back(temp);

        if (temp->Get_t() < earliest)
            earliest = temp->Get_t();
    };

    std::shared_ptr<Collision> temp = active_player->Inside(map_1.Fence_shape());
    
    if (temp->Get_t() != 2)
        active_player->Decrease_life();

    update_collided_and_earliest(collided, earliest, temp);

    temp = passive_player->Inside(map_1.Fence_shape());

    if (temp->Get_t() != 2)
        passive_player->Decrease_life();

    update_collided_and_earliest(collided, earliest, temp);

    temp = active_player->Between(*passive_player);

    update_collided_and_earliest(collided, earliest, temp);

    for (auto w : map_1.Get_wall())
    {
        temp = active_player->Between(w.Shape());

        update_collided_and_earliest(collided, earliest, temp);

        temp = passive_player->Between(w.Shape());

        update_collided_and_earliest(collided, earliest, temp);
    }

    for (auto c : collided)
        c->Update_translation(earliest);

    active_player->Update_displacement();
    passive_player->Update_displacement();
}