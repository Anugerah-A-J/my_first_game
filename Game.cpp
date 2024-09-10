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

    turn{Turn::magenta},
    fence{},
    magenta_king{},
    cyan_king{},
    aim{},
    clipper{},
    pawn_container{}
{
    std::ofstream Log{"log.txt"};
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
    if(test) 
        return;

    log("\ncouldn't initialize " + description);
    exit(1);
}

void Game::draw() const
{
    aim.draw();
    clipper.draw();
    cyan_king.draw();
    magenta_king.draw();
    fence.draw();
    pawn_container.draw();
}

void Game::update_aim(int x, int y)
{
    if (pawn_container.get_moving_pawn() != nullptr) // wait for moving pawn to stop
        return;

    if (pawn_container.dying_pawn_is_empty()) // wait for dying pawn to be dead
        return;

    if (turn == Turn::cyan && cyan_king.pointed_by(x, y))
    {
        aim.set_center(cyan_king.get_cx(), cyan_king.get_cy());
        aim.show();
        aim.update_xy(x, y);
        return;
    }
    if (turn == Turn::magenta && magenta_king.pointed_by(x, y))
    {
        aim.set_center(magenta_king.get_cx(), magenta_king.get_cy());
        aim.show();
        aim.update_xy(x, y);
        return;
    }

    if (turn == Turn::magenta)
    {
    	Pawn* mp { pawn_container.get_magenta_pointed_by(x, y) };

    	if (mp != nullptr)
    	{
    		aim.set_center(mp->get_cx(), mp->get_cy());
    		aim.show();
    	}
    }
    else if (turn == Turn::cyan)
    {
    	Pawn* cp { pawn_container.get_cyan_pointed_by(x, y) };

    	if (cp != nullptr)
    	{
    		aim.set_center(cp->get_cx(), cp->get_cy());
    		aim.show();
    	}
    }

    aim.update_xy(x, y);
}

void Game::logic()
{
    pawn_container.move();
    
    if (pawn_container.get_moving_pawn() != nullptr && !fence.contain(pawn_container.get_moving_pawn()))
    {
        fence.resolve(pawn_container.get_moving_pawn());
        pawn_container.add_dying_pawn(pawn_container.get_moving_pawn());
        pawn_container.stop();
    }

    // if (turn == Turn::magenta)
    //     pawn_container.trigger_dying_magenta();
    // else if (turn == Turn::cyan)
    //     pawn_container.trigger_dying_cyan();

    pawn_container.die();
    pawn_container.remove_dead_pawn();
}

void Game::produce_pawn(int x, int y)
{
    if (!aim.get_visible()) // wait for pawn to be selected
        return;
    
    if (pawn_container.get_moving_pawn() != nullptr) // wait for moving pawn to stop
        return;

    if (pawn_container.dying_pawn_is_empty()) // wait for dying pawn to be dead
        return;

    aim.hide();

    if (turn == Turn::magenta)
    {
        turn = Turn::cyan;
        aim.cyan();
        pawn_container.add_magenta(aim.get_cx(), aim.get_cy());
    }
    else if (turn == Turn::cyan)
    {
        turn = Turn::magenta;
        aim.magenta();
        pawn_container.add_cyan(aim.get_cx(), aim.get_cy());
    }
    
    pawn_container.update_dxdy(aim.get_x(), aim.get_y());
}

void Game::log(const std::string &description)
{
    std::ofstream Log{"log.txt", std::ios::app};
    Log << description;
    Log.close();
}

void Game::run()
{
    log("game init success");

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
                logic();

                log("\ntimer is ticking");
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                
                update_aim(event.mouse.x, event.mouse.y);
                
                log("\nmouse is moved");
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                
                if (event.mouse.button == 1)
                    produce_pawn(event.mouse.x, event.mouse.y);
                
                log("\nmouse is clicked");
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
            draw();
            al_flip_display();
            redraw = false;
            log("\ndrawing....");
        }
    }
}
