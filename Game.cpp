#include "Game.h"
#include "Parameter.h"
#include <iostream>

Game::Game()
{
    // al_init();
    // al_init_primitives_addon();
    // al_install_keyboard();
    // al_install_mouse();
}

Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void Game::draw() const
{
    if (state == State::cyan || state == State::magenta)
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

void Game::mouse_is_moved()
{
    switch (state)
    {
    case State::magenta:
        // wait for:
        // moving pawn to stop
        // all dying pawn to die
        if (!Pawn::finish_moving() || !dying_pawns.empty())
            return;

        if (magenta_king.pointed_by(mouse_coordinate))
        {
            aim.set_center(magenta_king.get_center());
            aim.show();
        }
        else
        {
            for (const auto& pawn_magenta: pawns_magenta)
            {
                if (pawn_magenta.pointed_by(mouse_coordinate))
                {
                    aim.set_center(pawn_magenta.get_center());
                    aim.show();
                }
            }
        }

        aim.rotate(mouse_coordinate);
        
        break;

    case State::cyan:
        // wait for:
        // moving pawn to stop
        // all dying pawn to die
        if (!Pawn::finish_moving() || !dying_pawns.empty())
            return;

        if (cyan_king.pointed_by(mouse_coordinate))
        {
            aim.set_center(cyan_king.get_center());
            aim.show();
        }
        else
        {
            for (const auto& pawn_cyan: pawns_cyan)
            {
                if (pawn_cyan.pointed_by(mouse_coordinate))
                {
                    aim.set_center(pawn_cyan.get_center());
                    aim.show();
                }
            }
        }
        
        aim.rotate(mouse_coordinate);
        
        break;
    
    default:
        break;
    }
}

void Game::logic()
{
    switch (state)
    {
    case State::magenta:
        // wait for:
        // there is a moving pawn
        // there is at least a pawn
        if (Pawn::finish_moving() || pawns_magenta.empty())
            return;

        pawns_magenta.back().move();

        collision_engine(dying_pawns, pawns_magenta.back(), fence);

        if (Pawn::finish_moving())
        {
            state = State::cyan;
            aim.cyan();
        }

        kill_and_delete_pawns();

        break;

    case State::cyan:
        // wait for:
        // there is a moving pawn
        // there is at least a pawn
        if (Pawn::finish_moving() || pawns_cyan.empty())
            return;
        
        pawns_cyan.back().move();

        collision_engine(dying_pawns, pawns_cyan.back(), fence);

        if (Pawn::finish_moving())
        {
            state = State::magenta;
            aim.magenta();
        }

        kill_and_delete_pawns();

        break;
    
    default:
        break;
    }
}

void Game::kill_and_delete_pawns()
{
    for(int i{0}; i < dying_pawns.size(); i++)
    {
        // if (!dying_pawns.at(i)->is_dead())
        // {
        //     dying_pawns.at(i)->die();
        //     continue;
        // }

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

void Game::mouse_is_left_clicked()
{
    switch (state)
    {
    case State::magenta:
        // wait for:
        // moving pawn to stop
        // pawn to be selected
        if (!Pawn::finish_moving() || !aim.is_visible())
            return;
    
        aim.hide();

        pawns_magenta.emplace_back(
            Pawn(
                aim.get_center().get_x(),
                aim.get_center().get_y(),
                Parameter::magenta()
            )
        );
    
        Pawn::update_d(aim.get_center(), aim.get_endpoint());
        Pawn::reset_move_step_count();
        
        break;

    case State::cyan:
        // wait for:
        // moving pawn to stop
        // pawn to be selected
        if (!Pawn::finish_moving() || !aim.is_visible())
            return;
    
        aim.hide();

        pawns_cyan.emplace_back(
            Pawn(
                aim.get_center().get_x(),
                aim.get_center().get_y(),
                Parameter::cyan()
            )
        );
    
        Pawn::update_d(aim.get_center(), aim.get_endpoint());
        Pawn::reset_move_step_count();

        break;
    
    default:
        break;
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

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                logic();
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                mouse_coordinate = Vector(event.mouse.x, event.mouse.y);
                mouse_is_moved();
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                mouse_coordinate = Vector(event.mouse.x, event.mouse.y);
                if (event.mouse.button == 1)
                    mouse_is_left_clicked();
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