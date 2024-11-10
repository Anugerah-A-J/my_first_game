#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
// #include <string>
#include "object.h"
#include "character.h"
#include <vector>
#include <set>
#include <iostream>
#include "collision.h"
#pragma once

enum class State
{
    choose,
    aim,
    shoot,
    end
};

// enum struct Turn
// {
//     magenta,
//     cyan,
//     neutral
// };

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void draw() const;
    void update_aim_center(float x, float y);
    void update_aim_direction(float x, float y);
    void add_pawn();
    void move_pawn();
    void clean_pawn();

    State state;
    // Turn turn;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;

    Fence fence;
    Clipper clipper;
    Aim aim;
    King_magenta king_magenta;
    King_cyan king_cyan;
    std::vector<Pawn> pawns_magenta;
    std::vector<Pawn> pawns_cyan;

    King* active_king = &king_magenta;
    King* passive_king = &king_cyan;
    std::vector<Pawn>* active_pawns = &pawns_magenta;
    std::vector<Pawn>* passive_pawns = &pawns_cyan;
    std::set<Pawn*> vanishing_pawns;

    // Widget end;

    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};

Game::Game()
:
    state{State::choose},

    timer{},
    queue{},
    display{},

    fence{},
    clipper{},
    aim{},
    king_magenta{},
    king_cyan{},
    pawns_magenta{},
    pawns_cyan{},

    active_king{&king_magenta},
    passive_king{&king_cyan},
    active_pawns{&pawns_magenta},
    passive_pawns{&pawns_cyan}
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    timer = al_create_timer(1.0 / 30.0);
    queue = al_create_event_queue();
    display = al_create_display(param::window_width, param::window_height);

    // al_set_window_position(display, 0, 0);
}

Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void Game::draw() const
{
    al_clear_to_color(param::black);
    
    aim.draw();
    king_cyan.draw();
    king_magenta.draw();

    for (const auto& pawn_magenta: pawns_magenta)
    {
        pawn_magenta.draw();
    }

    for (const auto& pawn_cyan: pawns_cyan)
    {
        pawn_cyan.draw();
    }

    clipper.draw();
    fence.draw();
    king_cyan.draw_life();
    king_magenta.draw_life();
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
                if (state == State::shoot)
                {
                    move_pawn();
                    clean_pawn();
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

                if (event.mouse.button == 1 && state == State::aim)
                    add_pawn();
            
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:

                if (state == State::choose)
                    update_aim_center(event.mouse.x, event.mouse.y);
            
                else if (state == State::aim)
                    update_aim_direction(event.mouse.x, event.mouse.y);
            
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

void Game::update_aim_center(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);
    
    if (active_king->contain(mouse_coordinate))
    {
        aim.center(active_king->center());
        aim.show();
        state = State::aim;
    }
    else
    {
        for (const auto &pawn : *active_pawns)
        {
            if (pawn.contain(mouse_coordinate))
            {
                aim.center(pawn.center());
                aim.show();
                state = State::aim;
            }
        }
    }
}

void Game::update_aim_direction(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);
    
    if (active_king->contain(mouse_coordinate))
        aim.center(active_king->center());

    else
        for (const auto &pawn : *active_pawns)
            if (pawn.contain(mouse_coordinate))
                aim.center(pawn.center());

    aim.update_direction(mouse_coordinate);
}

void Game::add_pawn()
{
    aim.hide();

    active_pawns->emplace_back(Pawn(
        aim.center(),
        active_king->color()
    ));

    Pawn::update_translation(aim.center(), aim.pawn_destination());
    Pawn::reset_translation_step_count();
    state = State::shoot;
}

void Game::move_pawn()
{
    active_pawns->back().move();

    collision::response(vanishing_pawns, active_pawns->back(), *passive_pawns);

    collision::response(active_pawns->back(), *active_king, [&](float t)
    {
        if (!active_king->contain(aim.center())) // when pawn doesn't come out of king
        {
            active_pawns->back().retreat(1 - t);
            active_pawns->back().stop();
        }
    });

    collision::response(active_pawns->back(), *passive_king, [&](float f)
    {
        Pawn::vanish_immediately(true);

        f = collision::circle_vs_circle(
            active_pawns->back().shape(),
            passive_king->king_shape(),
            active_pawns->back().last_translation()
        );
        std::cout << "t = " << f << "\n";

        if (f <= 1)
        {
            passive_king->life_decrease_by(1);
            std::cout << "king lives" << passive_king->life() << "\n";
        }
    });

    collision::response(vanishing_pawns, active_pawns->back(), fence);
}

void Game::clean_pawn()
{
    if (Pawn::vanish_immediately())
    {
        active_pawns->pop_back();
        Pawn::vanish_immediately(false);
    }
    else if (vanishing_pawns.empty() && Pawn::finish_moving())
    {
        std::swap(active_king, passive_king);
        std::swap(active_pawns, passive_pawns);

        state = State::choose;
        aim.color(active_king->color());
        // std::cout << "move pawn > choose and aim\n";
    }

    for(auto it = vanishing_pawns.begin(); it != vanishing_pawns.end();)
    {
        if (!(*it)->color_equal_vanish())
        {
            (*it)->transform_color_to_vanish();
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
    
        it = vanishing_pawns.erase(it);
    }
}