#include "Game.h"
#include "Parameter.h"
#include <iostream>

// Game::Game()
// {
//     // al_init();
//     // al_init_primitives_addon();
//     // al_install_keyboard();
//     // al_install_mouse();
// }

Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void Game::draw() const
{
    if (state != State::end)
    {
        al_clear_to_color(Parameter::black());
        aim.draw();
        clipper.draw();
        cyan_king.draw();
        magenta_king.draw();
        fence.draw();
        
        for (const auto& pawn_magenta: pawns_magenta)
        {
            pawn_magenta.draw();
        }

        for (const auto& pawn_cyan: pawns_cyan)
        {
            pawn_cyan.draw();
        }
    }
}

void Game::kill_and_delete_pawns()
{
    for(int i = 0; i < dying_pawns.size(); i++)
    {
        if (!dying_pawns.at(i)->is_dead())
        {
            dying_pawns.at(i)->die();
            continue;
        }

        if (dying_pawns.at(i) >= &pawns_magenta.front() && dying_pawns.at(i) <= &pawns_magenta.back())
        {
            pawns_magenta.erase(pawns_magenta.begin() + (dying_pawns.at(i) - &pawns_magenta.front()));
        }
        else if (dying_pawns.at(i) >= &pawns_cyan.front() && dying_pawns.at(i) <= &pawns_cyan.back())
        {
            pawns_cyan.erase(pawns_cyan.begin() + (dying_pawns.at(i) - &pawns_cyan.front()));
        }
       
        dying_pawns.erase(dying_pawns.begin() + i);
    }
}

void Game::update_aim(State& state)
{
    if (state != State::choose_and_aim)
        return;

    if (turn == Turn::magenta)
    {
        if (magenta_king.pointed_by(mouse_coordinate))
        {
            aim.set_center(magenta_king.get_center());
            aim.show();
        }
        else
        {
            for (const auto &pawn_magenta : pawns_magenta)
            {
                if (pawn_magenta.pointed_by(mouse_coordinate))
                {
                    aim.set_center(pawn_magenta.get_center());
                    aim.show();
                }
            }
        }
    }
    else if (turn == Turn::cyan)
    {
        if (cyan_king.pointed_by(mouse_coordinate))
        {
            aim.set_center(cyan_king.get_center());
            aim.show();
        }
        else
        {
            for (const auto &pawn_cyan : pawns_cyan)
            {
                if (pawn_cyan.pointed_by(mouse_coordinate))
                {
                    aim.set_center(pawn_cyan.get_center());
                    aim.show();
                }
            }
        }
    }
    aim.rotate(mouse_coordinate);
}

void Game::add_pawn(State& state)
{
    if (state != State::choose_and_aim && !aim.is_visible())
        return;

    aim.hide();

    if (turn == Turn::magenta)
    {
        pawns_magenta.emplace_back(
            Pawn(
                aim.get_center().get_x(),
                aim.get_center().get_y(),
                Parameter::magenta()
            )
        );
        std::cout << "magenta pawn added\n";
    }
    else if (turn == Turn::cyan)
    {
        pawns_cyan.emplace_back(
            Pawn(
                aim.get_center().get_x(),
                aim.get_center().get_y(),
                Parameter::cyan()
            )
        );
    }

    Pawn::update_d(aim.get_center(), aim.get_endpoint());
    Pawn::reset_move_step_count();
    state = State::move_pawn;
    std::cout << "state is changed to move pawn\n";
}

void Game::move_pawn(State &state)
{
    if (state != State::move_pawn)
        return;

    if (turn == Turn::magenta)
    {
        if (pawns_magenta.empty())
            return;

        if (!Pawn::finish_moving())
        {
            pawns_magenta.back().move();
            collision_engine(dying_pawns, pawns_magenta.back(), fence);
            std::cout << "magenta moved\n";
        }
        else
        {
            turn = Turn::cyan;
            state = State::choose_and_aim;
            aim.cyan();
        }
    }
    else if (turn == Turn::cyan)
    {
        if (pawns_cyan.empty())
            return;

        if (!Pawn::finish_moving())
        {
            pawns_cyan.back().move();
            collision_engine(dying_pawns, pawns_cyan.back(), fence);
        }
        else
        {
            turn = Turn::magenta;
            state = State::choose_and_aim;
            aim.magenta();
        }
    }
}

void Game::run()
{
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(true)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                move_pawn(state);
                kill_and_delete_pawns();
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                mouse_coordinate = Vector(event.mouse.x, event.mouse.y);
                update_aim(state);
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button == 1)
                    add_pawn(state);
                break;

            case ALLEGRO_EVENT_KEY_DOWN:

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            draw();
            al_flip_display();
            redraw = false;
        }
    }
}