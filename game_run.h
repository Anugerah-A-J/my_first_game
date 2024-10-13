#include "Game.hpp"

void draw(Game& game)
{
    if (game.state != State::end)
    {
        al_clear_to_color(param::black);
        
        game.aim.draw();
        // king_cyan.draw();
        // king_magenta.draw();
        
        game.clipper.draw();
        game.fence.draw();

        // for (const auto& pawn_magenta: pawns_magenta)
        // {
        //     pawn_magenta.draw();
        // }

        // for (const auto& pawn_cyan: pawns_cyan)
        // {
        //     pawn_cyan.draw();
        // }
    }
};

void run(Game& game)
{
    al_register_event_source(game.queue, al_get_keyboard_event_source());
    al_register_event_source(game.queue, al_get_display_event_source(game.display));
    al_register_event_source(game.queue, al_get_timer_event_source(game.timer));
    al_register_event_source(game.queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(game.timer);

    while(true)
    {
        al_wait_for_event(game.queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // move_pawn(state);
                // kill_and_delete_pawns();
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                // mouse_coordinate = Vector(event.mouse.x, event.mouse.y);
                // update_aim(state);
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

        if(redraw && al_is_event_queue_empty(game.queue))
        {
            draw(game);
            al_flip_display();
            redraw = false;
        }
    }
};