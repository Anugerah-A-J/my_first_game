#include "Game.hpp"
#pragma once

Game::Game()
:
    active_player{&player_magenta},
    passive_player{&player_cyan},
    map_1{},
    exit{false},
    mouse_position{0, 0},
    what_to_do{&aiming}
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    timer = al_create_timer(1.0 / 30.0);
    queue = al_create_event_queue();
    display = al_create_display(Param::window_width, Param::window_height);
    font = al_create_builtin_font();
    // al_set_window_position(display_, 0, 0);
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

    bool redraw = true;
    ALLEGRO_EVENT event;

    End_dialog_box end_dialog_box = End_dialog_box(font);
    pointer_to_end_dialog_box = &end_dialog_box;

    al_start_timer(timer);

    while (true) {
        al_wait_for_event(queue, &event);

        // switch (event.type) {
        // case ALLEGRO_EVENT_TIMER:
        //     if (state == State::shoot) {
        //         Move_pawn();
        //         Clean_pawn();
        //     }
        //     redraw = true;
        //     break;

        // case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

        //     if (event.mouse.button == 1 && state == State::aim)
        //         Add_pawn();

        //     else if (event.mouse.button == 1 && state == State::end)
        //         Play_again_or_quit(done);

        //     break;

        // case ALLEGRO_EVENT_MOUSE_AXES:

        //     if (state == State::choose)
        //         Update_aim_center(event.mouse.x, event.mouse.y);

        //     else if (state == State::aim)
        //         Update_aim_direction(event.mouse.x, event.mouse.y);

        //     else if (state == State::end)
        //         pointer_to_end_dialog_box->Update_selected_choice(
        //             Vector(event.mouse.x, event.mouse.y));

        //     break;

        // case ALLEGRO_EVENT_KEY_CHAR:
        //     if (state == State::end)
        //         pointer_to_end_dialog_box->Update_selected_choice(event.keyboard.keycode);

        //     if (state == State::end && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
        //         Play_again_or_quit(done);

        //     if (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
        //         break;
        // }
        (*what_to_do)();

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = true;

        if (exit)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            Draw();
            al_flip_display();
            redraw = false;
        }
    }
}

void Game::Draw() const
{
    al_clear_to_color(Param::black);

    aim.Draw();
    player_cyan.Draw();
    player_magenta.Draw();

    clipper.Draw();
    map_1.Draw();
    player_cyan.Draw_life();
    player_magenta.Draw_life();

    pointer_to_end_dialog_box->Draw();
}

void Game::Update_aim_center(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);

    if (active_king->Contain(mouse_coordinate)) {
        aim.Center(active_king->Center());
        aim.Show_reach_circle();
        state = State::aim;
    } else {
        for (const auto& pawn : *active_pawns) {
            if (pawn.Contain(mouse_coordinate)) {
                aim.Center(pawn.Center());
                aim.Show_reach_circle();
                state = State::aim;
            }
        }
    }
}

void Game::Update_aim_direction(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);

    if (active_king->Contain(mouse_coordinate))
        aim.Center(active_king->Center());

    else
        for (const auto& pawn : *active_pawns)
            if (pawn.Contain(mouse_coordinate))
                aim.Center(pawn.Center());

    aim.Update_direction(mouse_coordinate);
    aim.Show_direction_sign();
}

void Game::Add_pawn()
{
    aim.Hide();

    active_pawns->emplace_back(aim.Center(), active_king->Color());

    Pawn::Update_translation(aim.Center(), aim.Pawn_destination());
    Pawn::Reset_translation_step_count();
    state = State::shoot;
}

void Game::Move_pawn()
{
    active_pawns->back().Move();
    // trail.emplace_back(active_pawns->back().Last_translation());

    active_pawns->back().Kill(*passive_pawns, vanishing_pawns);

    active_pawns->back().Stopped_by(*active_king, aim.Center());
    active_pawns->back().Hurt(*passive_king);

    map_1.Wall_stop(active_pawns->back());
    map_1.Tree_stop(active_pawns->back());
    map_1.X_kill(active_pawns->back(), vanishing_pawns);
    map_1.Window_only_shoot(active_pawns->back());

    fence.Kill(active_pawns->back(), vanishing_pawns);
}

void Game::Clean_pawn()
{
    if (Pawn::Vanish_immediately() && Pawn::Finish_moving()) {
        active_pawns->pop_back();
        Pawn::Vanish_immediately(false);
    } else if (vanishing_pawns.empty() && Pawn::Finish_moving()) {
        passive_king->Update_life();

        if (passive_king->Life() == 0) {
            std::string message = passive_king == &king_magenta ? "Cyan Win" : "Magenta Win";
            pointer_to_end_dialog_box->Add_message(message, active_king->Color());
            state = State::end;
        } else {
            std::swap(active_king, passive_king);
            std::swap(active_pawns, passive_pawns);

            state = State::choose;
            aim.Color(active_king->Color());
        }
    }

    for (auto it = vanishing_pawns.begin(); it != vanishing_pawns.end();) {
        if (!(*it)->Color_equal_vanish()) {
            (*it)->Transform_color_to_vanish();
            ++it;
            continue;
        }

        if (*it >= &pawns_magenta.front() && *it <= &pawns_magenta.back()) {
            pawns_magenta.erase(pawns_magenta.begin() + (*it - &pawns_magenta.front()));
        } else if (*it >= &pawns_cyan.front() && *it <= &pawns_cyan.back()) {
            pawns_cyan.erase(pawns_cyan.begin() + (*it - &pawns_cyan.front()));
        }

        it = vanishing_pawns.erase(it);
    }
}

void Game::Play_again_or_quit(bool& done)
{
    switch (pointer_to_end_dialog_box->Selected_choice_index()) {
    case 0:
        aim.Color(Param::magenta);

        player_cyan.Reset_life();
        player_magenta.Reset_life();

        active_player = &player_magenta;
        passive_player = &player_cyan;

        state = &aiming;

        pointer_to_end_dialog_box->Erase_message();

        break;

    case 1:
        done = true;
        break;

    default:
        break;
    }
}
