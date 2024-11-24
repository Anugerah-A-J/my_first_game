#include <allegro5/allegro5.h>
// #include <allegro5/allegro_primitives.h>
// #include <string>
#include "object.h"
#include "character.h"
#include <vector>
#include <set>
#include "collision.h"
#include "ui.h"
#pragma once

enum class State
{
    choose,
    aim_,
    shoot,
    end
};

class Game
{
public:
    Game();
    ~Game();
    void Run();
private:
    void Draw() const;
    void Update_aim_center(float x, float y);
    void Update_aim_direction(float x, float y);
    void Add_pawn();
    void Move_pawn();
    void Clean_pawn();

    State state;
    // Turn turn;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* font;

    Fence fence;
    Clipper clipper;
    Aim aim;
    King_magenta king_magenta;
    King_cyan king_cyan;
    std::vector<Pawn> pawns_magenta;
    std::vector<Pawn> pawns_cyan;

    King* active_king;
    King* passive_king;
    std::vector<Pawn>* active_pawns;
    std::vector<Pawn>* passive_pawns;
    std::set<Pawn*> vanishing_pawns;

    End end;

    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};

Game::Game()
:
    state{State::choose},
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
    font = al_create_builtin_font();

    One_line_text::Font(font);

    // al_set_window_position(display_, 0, 0);
}

Game::~Game()
{
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void Game::Draw() const
{
    al_clear_to_color(param::black);
    
    aim.Draw();
    king_cyan.Draw();
    king_magenta.Draw();

    for (const auto& pawn_magenta: pawns_magenta)
    {
        pawn_magenta.Draw();
    }

    for (const auto& pawn_cyan: pawns_cyan)
    {
        pawn_cyan.Draw();
    }

    clipper.Draw();
    fence.Draw();
    king_cyan.Draw_life();
    king_magenta.Draw_life();

    if (state == State::end)
        end.Draw();
}

void Game::Run()
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
                    Move_pawn();
                    Clean_pawn();
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

                if (event.mouse.button == 1 && state == State::aim_)
                    Add_pawn();

                else if (event.mouse.button == 1 && state == State::end)
                    Play_again_or_quit(event.mouse.x, event.mouse.y);
            
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:

                if (state == State::choose)
                    Update_aim_center(event.mouse.x, event.mouse.y);
            
                else if (state == State::aim_)
                    Update_aim_direction(event.mouse.x, event.mouse.y);

                else if (state == State::end)
                    Highlight_end_choices(event.mouse.x, event.mouse.y);
            
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                Highlight_end_choices(event.keyboard.keycode);

                if (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                    break;
                
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            Draw();
            al_flip_display();
            redraw = false;
        }
    }
}

void Game::Update_aim_center(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);
    
    if (active_king->Contain(mouse_coordinate))
    {
        aim.Center(active_king->Center());
        aim.Show_reach_circle();
        state = State::aim_;
    }
    else
    {
        for (const auto &pawn : *active_pawns)
        {
            if (pawn.Contain(mouse_coordinate))
            {
                aim.Center(pawn.Center());
                aim.Show_reach_circle();
                state = State::aim_;
            }
        }
    }
}

void Game::Update_aim_direction(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);
    
    if (active_king->Contain(mouse_coordinate))
        aim.Center(active_king->Center());

    else
        for (const auto &pawn : *active_pawns)
            if (pawn.Contain(mouse_coordinate))
                aim.Center(pawn.Center());

    aim.Update_direction(mouse_coordinate);
    aim.Show_direction_sign();
}

void Game::Add_pawn()
{
    aim.Hide();

    active_pawns->emplace_back(Pawn(
        aim.Center(),
        active_king->Color()
    ));

    Pawn::Update_translation(aim.Center(), aim.Pawn_destination());
    Pawn::Reset_translation_step_count();
    state = State::shoot;
}

void Game::Move_pawn()
{
    active_pawns->back().Move();

    collision::Response(vanishing_pawns, active_pawns->back(), *passive_pawns);

    collision::Response(active_pawns->back(), *active_king, [&](float t)
    {
        if (!active_king->Contain(aim.Center())) // when pawn doesn't come out of king
        {
            active_pawns->back().Retreat(1 - t);
            active_pawns->back().Stop();
        }
    });

    collision::Response(active_pawns->back(), *passive_king, [&](float f)
    {
        Pawn::Vanish_immediately(true);

        f = collision::Circle_vs_circle(
            active_pawns->back().Shape(),
            passive_king->King_shape(),
            active_pawns->back().Last_translation()
        );

        if (f <= 1)
            passive_king->Life_decrease_by(1);
    });

    collision::Response(vanishing_pawns, active_pawns->back(), fence);
}

void Game::Clean_pawn()
{
    if (Pawn::Vanish_immediately() && Pawn::Finish_moving())
    {
        active_pawns->pop_back();
        Pawn::Vanish_immediately(false);
    }
    else if (vanishing_pawns.empty() && Pawn::Finish_moving())
    {
        std::swap(active_king, passive_king);
        std::swap(active_pawns, passive_pawns);

        state = State::choose;
        aim.Color(active_king->Color());
        // std::cout << "move pawn > choose and aim_\n";
    }

    for(auto it = vanishing_pawns.begin(); it != vanishing_pawns.end();)
    {
        if (!(*it)->Color_equal_vanish())
        {
            (*it)->Transform_color_to_vanish();
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