#include "Game.hpp"

Game::Game()
:
    al_init_is_success{al_init()},
    al_init_primitives_addon_is_success{al_init_primitives_addon()},
    al_install_keyboard_is_success{al_install_keyboard()},
    al_install_mouse_is_success{al_install_mouse()},

    timer{al_create_timer(1.0 / 30.0)},
    queue{al_create_event_queue()},
    display{al_create_display(Param::window_width, Param::window_height)},
    font{al_create_builtin_font()},

    // end_dialog_box{font},

    player_magenta{map_1},
    player_cyan{map_1},

    active_player{&player_magenta},
    passive_player{&player_cyan},
    what_to_do{&aiming},

    mouse_position{0, 0},
    exit{false}
{
    aiming = [&]()
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
            active_player->Update_translation(aim.Center(), aim.End_point());
        }
    };

    moving = [&]()
    {
        if (event.type != ALLEGRO_EVENT_TIMER)
            return;

        active_player->Move(map_1, passive_player);
        // trail.emplace_back(active_pawns->back().Last_translation());
        // active_player->Reflect(*passive_player);

        // map_1.Reflect(active_player);
        // map_1.Reflect_and_hurt(active_player);

        if (active_player->Finish_moving() && passive_player->Finish_moving())
        {
            passive_player->Update_life();
            active_player->Update_life();

            // if (passive_player->Dead())
            // {
            //     std::string message = passive_player == &player_magenta ? "Cyan Win" : "Magenta Win";
            //     end_dialog_box.Add_message(message, active_player->Color());
            //     end_dialog_box.Show();
            //     what_to_do = &ending;
            // }
            // else
            // {
                std::swap(active_player, passive_player);
                aim.Color(active_player->Color());
                what_to_do = &aiming;
            // }
        }
    };

    // ending = [&]()
    // {
    //     if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode != ALLEGRO_KEY_ENTER)
    //     {
    //         end_dialog_box.Update_selected_choice(event.keyboard.keycode);
    //     }
    //     else if (event.type == ALLEGRO_EVENT_MOUSE_AXES && event.mouse.button != 1)
    //     {
    //         end_dialog_box.Update_selected_choice(mouse_position);
    //     }
    //     else if (
    //         (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ENTER) &&
    //         (event.type == ALLEGRO_EVENT_MOUSE_AXES && event.mouse.button == 1))
    //     {
    //         switch (end_dialog_box.Selected_choice_index())
    //         {
    //         case 0:
    //             aim.Color(Param::magenta);

    //             player_cyan.Reset_life();
    //             player_magenta.Reset_life();

    //             active_player = &player_magenta;
    //             passive_player = &player_cyan;

    //             what_to_do = &aiming;

    //             end_dialog_box.Erase_message();
    //             end_dialog_box.Hide();

    //             break;
    //         case 1:
    //             exit = true;
    //             break;
    //         default:
    //             break;
    //         }
    //     }
    // };
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

        bool window_is_closed = event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
        bool esc_is_pressed = event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;

        if (window_is_closed || esc_is_pressed)
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
    // end_dialog_box.Draw();

    // std::string mx = std::to_string(player_magenta.Center().X());
    // std::string my = std::to_string(player_magenta.Center().Y());
    // std::string cx = std::to_string(player_cyan.Center().X());
    // std::string cy = std::to_string(player_cyan.Center().Y());
    // std::string max_x = std::to_string(map_1.Fence_shape().Bottom_right().X());
    // std::string max_y = std::to_string(map_1.Fence_shape().Bottom_right().Y());
    //
    // std::string text_m = "Magenta: " + mx + ", " + my;
    // std::string text_c = "Cyan: " + cx + ", " + cy;
    //
    // al_draw_text(font, Param::white, Param::window_width / 2, Param::unit_length, ALLEGRO_ALIGN_CENTER, &text_m.front());
    // al_draw_text(font, Param::white, Param::window_width / 2, Param::unit_length * 2, ALLEGRO_ALIGN_CENTER, &text_c.front());
    // al_draw_text(font, Param::white, std::stof(max_x), std::stof(max_y), ALLEGRO_ALIGN_LEFT, &max_x.front());
    // al_draw_text(font, Param::white, std::stof(max_x), std::stof(max_y) + Param::unit_length, ALLEGRO_ALIGN_LEFT, &max_y.front());
}
