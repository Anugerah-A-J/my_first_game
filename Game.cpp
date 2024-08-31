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
    clipper{},
    fence{},
    magenta_king{},
    cyan_king{},
    aim{},
    magenta_pawn{},
    cyan_pawn{},
    pawn_mover{}
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

void Game::update_aim(int x, int y)
{
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

    int i {index_of_pawn_pointed_by(x, y)};

    if (turn == Turn::magenta && i != -1)
    {
        aim.set_center(magenta_pawn.at(i).get_cx(), magenta_pawn.at(i).get_cy());
        aim.show();
    }
    else if (turn == Turn::cyan && i != -1)
    {
        aim.set_center(cyan_pawn.at(i).get_cx(), cyan_pawn.at(i).get_cy());
        aim.show();
    }

    aim.update_xy(x, y);
}

int Game::index_of_pawn_pointed_by(int x, int y)
{
    if (turn == Turn::magenta)
    {
        for (int i = 0; i < magenta_pawn.size(); i++)
        {
            if (magenta_pawn.at(i).pointed_by(x, y))
                return i;
        }
    }
    else if (turn == Turn::cyan)
    {
        for (int i = 0; i < cyan_pawn.size(); i++)
        {
            if (cyan_pawn.at(i).pointed_by(x, y))
                return i;
        }
    }
    
    return -1;
}

void Game::produce_pawn(unsigned int button, int x, int y)
{
    if (button != 1 || !aim.get_visible() || !pawn_mover.finish())
        return;

    aim.hide();

    if (turn == Turn::magenta)
    {
        turn = Turn::cyan;
        aim.cyan();
        magenta_pawn.emplace_back(Magenta_pawn(aim.get_cx(), aim.get_cy()));
        pawn_mover.set_pawn(&magenta_pawn.back());
    }
    else if (turn == Turn::cyan)
    {
        turn = Turn::magenta;
        aim.magenta();
        cyan_pawn.emplace_back(Cyan_pawn(aim.get_cx(), aim.get_cy()));
        pawn_mover.set_pawn(&cyan_pawn.back());
    }
    
    pawn_mover.update_dxdy(aim.get_cx(), aim.get_cy(), aim.get_x(), aim.get_y());
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
                if (!pawn_mover.finish())
                    pawn_mover.move();
                    
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                update_aim(event.mouse.x, event.mouse.y);
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                produce_pawn(event.mouse.button, event.mouse.x, event.mouse.y);
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
            cyan_king.draw();
            magenta_king.draw();
            fence.draw();

            for (Magenta_pawn& mp : magenta_pawn)
                mp.draw();

            for (Cyan_pawn& cp : cyan_pawn)
                cp.draw();

            al_flip_display();

            redraw = false;
        }
    }
}