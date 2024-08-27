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
    white_king{},
    black_king{},
    aim{},
    aim_on{false},
    white_pawn{},
    black_pawn{}
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
        aim_on = true;
        aim.update_xy(x, y);
        return;
    }
    if (turn == Turn::white && white_king.pointed_by(x, y))
    {
        aim.set_center(white_king.get_cx(), white_king.get_cy());
        aim_on = true;
        aim.update_xy(x, y);
        return;
    }

    int i {index_of_pawn_pointed_by(x, y)};

    if (turn == Turn::white && i != -1)
    {
        aim.set_center(white_pawn.at(i).get_cx(), white_pawn.at(i).get_cy());
        aim_on = true;
    }
    else if (turn == Turn::black && i != -1)
    {
        aim.set_center(black_pawn.at(i).get_cx(), black_pawn.at(i).get_cy());
        aim_on = true;
        log("\nblack pawn is pointed");
    }

    if (aim_on)
        aim.update_xy(x, y);
}

int Game::index_of_pawn_pointed_by(int x, int y)
{
    if (turn == Turn::white)
        for (int i = 0; i < white_pawn.size(); i++)
            if (white_pawn.at(i).pointed_by(x, y))
                return i;

    if (turn == Turn::black) // else if fails
        for (int i = 0; i < black_pawn.size(); i++)
            if (black_pawn.at(i).pointed_by(x, y))
                return i;
    
    return -1;
}

void Game::produce_pawn(unsigned int button, int x, int y)
{
    if (button != 1 || !aim_on)
        return;

    // add another guard here for clicking when there is no aim (using bool aim_on, aim does not need show() and hide())

    // aim.hide();
    aim_on = false;

    if (turn == Turn::white)
    {
        turn = Turn::black;
        white_pawn.emplace_back(White_pawn(aim.get_x(), aim.get_y()));
    }
    else if (turn == Turn::black)
    {
        turn = Turn::white;
        black_pawn.emplace_back(Black_pawn(aim.get_x(), aim.get_y()));
    }
}

void Game::log(const std::string &description)
{
    std::ofstream Log{"log.txt", std::ios::app};
    Log << description;
    Log.close();
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
                // move_pawn();
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

            if (aim_on)
                aim.draw();
            
            clipper.draw();
            black_king.draw();
            white_king.draw();
            fence.draw();

            for (White_pawn& wp : white_pawn)
                wp.draw();

            for (Black_pawn& bp : black_pawn)
                bp.draw();

            // al_draw_filled_rectangle(0, 0, 340, 340, al_map_rgba_f(1, 1, 1, 0));

            al_flip_display();

            redraw = false;
        }
    }
}