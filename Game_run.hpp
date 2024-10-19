#include "Game.hpp"
#pragma once

void Game::draw() const
{
    if (state != State::end)
    {
        al_clear_to_color(param::black);
        
        aim.draw();
        king_cyan.draw();
        king_magenta.draw();
        
        clipper.draw();
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
};

void Game::run()
{
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    // ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(true)
    {
        al_wait_for_event(queue, &event);

        update_aim();
        update_pawn();

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // move_pawn(state);
                // kill_and_delete_pawns();
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                // if (event.mouse.button == 1)
                //     add_pawn(state);
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
};