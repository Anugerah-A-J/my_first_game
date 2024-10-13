#include "Game.h"
#include "Parameter.h"
#include <iostream>

Game::Game()
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_set_window_position(display, 0, 0);
}

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
        king_cyan.draw();
        king_magenta.draw();
        fence.draw();
        
        for (const auto& pawn_magenta: pawns_magenta)
        {
            pawn_magenta.draw();
        }

        for (const auto& pawn_cyan: pawns_cyan)
        {
            pawn_cyan.draw();
        }

        // clipper.draw();
    }
}

void Game::kill_and_delete_pawns()
{
    for(auto it = dying_pawns.begin(); it != dying_pawns.end();)
    {
        if (!(*it)->is_dead())
        {
            (*it)->die();
            ++it;
            continue;
        }

        if (*it >= &pawns_magenta.front() && *it <= &pawns_magenta.back())
        {
            pawns_magenta.erase(pawns_magenta.begin() + (*it - &pawns_magenta.front()));
        }
        else if (*it >= &pawns_cyan.front() && *it <= &pawns_cyan.back())
        {
            pawns_cyan.erase(pawns_cyan.begin() + (*it - &pawns_cyan.front()));
        }
       
        it = dying_pawns.erase(it);
    }
}

void Game::update_aim(State& state)
{
    if (state != State::choose_and_aim)
        return;

    if (turn == Turn::magenta)
    {
        if (king_magenta.pointed_by(mouse_coordinate))
        {
            aim.set_center(king_magenta.get_center());
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
        if (king_cyan.pointed_by(mouse_coordinate))
        {
            aim.set_center(king_cyan.get_center());
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
            collision_engine(dying_pawns, pawns_magenta.back(), pawns_cyan);
            collision_engine(pawns_magenta.back(), king_cyan);
            collision_engine(dying_pawns, pawns_magenta.back(), fence);
        }
        else
        {
            if (Pawn::is_dead_immediately_after_finish_moving())
            {
                pawns_magenta.pop_back();
                Pawn::set_dead_immediately_after_finish_moving(false);
            }
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
            collision_engine(dying_pawns, pawns_cyan.back(), pawns_magenta);
            collision_engine(pawns_cyan.back(), king_magenta);
            collision_engine(dying_pawns, pawns_cyan.back(), fence);
        }
        else
        {
            if (Pawn::is_dead_immediately_after_finish_moving())
            {
                pawns_cyan.pop_back();
                Pawn::set_dead_immediately_after_finish_moving(false);
            }
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