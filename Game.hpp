#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
// #include <string>
#include "Fence.hpp"
#include "Aim.hpp"
#include "Clipper.hpp"
#include "King.hpp"
#include <vector>
#include "Pawn.hpp"
#include <set>
#pragma once

enum struct State
{
    choose_and_aim,
    move_pawn,
    end
};

// enum struct Turn
// {
//     magenta,
//     cyan,
//     neutral
// };

struct Game
{
    State state = State::choose_and_aim;
    // Turn turn;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT event;

    Fence fence;
    Clipper clipper;
    Aim aim;
    King_magenta king_magenta;
    King_cyan king_cyan;
    King* king = &king_magenta;
    
    std::vector<Pawn> pawns_magenta;
    std::vector<Pawn> pawns_cyan;
    std::vector<Pawn>* pawns;
    std::set<Pawn*> dying_pawns;

    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
    Game()
    {
        al_init();
        al_init_primitives_addon();
        al_install_keyboard();
        al_install_mouse();
        al_set_window_position(display, 0, 0);

        timer = al_create_timer(1.0 / 30.0);
        queue = al_create_event_queue();
        display = al_create_display(param::window_width, param::window_height);
    };

    ~Game()
    {
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
    };

    void run();
private:
    void draw() const;
    void update_aim();
    void update_pawn();
};