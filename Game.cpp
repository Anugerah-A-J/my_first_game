#include "Game.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>
#include <fstream>

Game::Game():
    al_init_success{ al_init() },
    
    al_init_primitives_addon_success{ al_init_primitives_addon() },
    
    al_install_keyboard_success{ al_install_keyboard() },
    
    al_install_mouse_success{ al_install_mouse() },
    
    timer{ al_create_timer(1.0 / 30.0) },
    
    queue{ al_create_event_queue() },
    
    display{
        al_create_display(
            Parameter::window_width, 
            Parameter::window_height
        )
    },

    turn{Turn::white},

    clipper{},
    fence{},
    black_king{},
    white_king{},
    aim{}
{
    std::ofstream Log{"log.txt"};
    Log << "errors:";
    Log.close();

    check(al_init_success, "allegro");
    check(al_install_keyboard_success, "keyboard");
    check(al_install_mouse_success, "mouse");
    check(timer, "timer");
    check(queue, "queue");
    check(display, "display");
    check(al_init_primitives_addon_success,"primitives");
}

Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void Game::check(bool test, const std::string& description)
{
    std::ofstream Log{"log.txt", std::ios::app};
    
    if(test) 
        return;

    Log << "\ncouldn't initialize " << description;
    Log.close();
    exit(1);
}

void Game::update_aim(int x, int y)
{
    if (turn == Turn::black && black_king.pointed_by(x, y))
    {
        aim.set_center(black_king.get_cx(), black_king.get_cy());
        aim.show();
    }
    else if (turn == Turn::white && white_king.pointed_by(x, y))
    {
        aim.set_center(white_king.get_cx(), white_king.get_cy());
        aim.show();
    }

    aim.update_xy(x, y);
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
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                update_aim(event.mouse.x, event.mouse.y);
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
            al_clear_to_color(Parameter::window_color());

            aim.draw();
            clipper.draw();
            black_king.draw();
            white_king.draw();
            fence.draw();

            al_flip_display();

            redraw = false;
        }
    }
}