#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
// #include <string>
#include "object.h"
#include "character.h"
#include <vector>
#include <set>
#include "collision.h"
#pragma once

enum class State
{
    choose,
    aim_,
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

    State state_;
    // Turn turn;

    ALLEGRO_TIMER* timer_;
    ALLEGRO_EVENT_QUEUE* queue_;
    ALLEGRO_DISPLAY* display_;

    Fence fence_;
    Clipper clipper_;
    Aim aim_;
    King_magenta king_magenta_;
    King_cyan king_cyan_;
    std::vector<Pawn> pawns_magenta_;
    std::vector<Pawn> pawns_cyan_;

    King* active_king_;
    King* passive_king_;
    std::vector<Pawn>* active_pawns_;
    std::vector<Pawn>* passive_pawns_;
    std::set<Pawn*> vanishing_pawns_;

    // Widget end;

    // Map Map_1:
    // Box box; // yellow
    // Tree tree; // green
    // X x; // red
    // Glass glass; // white
};

Game::Game()
:
    state_{State::choose},

    timer_{},
    queue_{},
    display_{},

    fence_{},
    clipper_{},
    aim_{},
    king_magenta_{},
    king_cyan_{},
    pawns_magenta_{},
    pawns_cyan_{},

    active_king_{&king_magenta_},
    passive_king_{&king_cyan_},
    active_pawns_{&pawns_magenta_},
    passive_pawns_{&pawns_cyan_}
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    timer_ = al_create_timer(1.0 / 30.0);
    queue_ = al_create_event_queue();
    display_ = al_create_display(param::window_width, param::window_height);

    // al_set_window_position(display_, 0, 0);
}

Game::~Game()
{
    al_destroy_display(display_);
    al_destroy_timer(timer_);
    al_destroy_event_queue(queue_);
}

void Game::draw() const
{
    al_clear_to_color(param::black);
    
    aim_.draw();
    king_cyan_.draw();
    king_magenta_.draw();

    for (const auto& pawn_magenta: pawns_magenta_)
    {
        pawn_magenta.draw();
    }

    for (const auto& pawn_cyan: pawns_cyan_)
    {
        pawn_cyan.draw();
    }

    clipper_.draw();
    fence_.draw();
    king_cyan_.draw_life();
    king_magenta_.draw_life();
}

void Game::run()
{
    al_register_event_source(queue_, al_get_keyboard_event_source());
    al_register_event_source(queue_, al_get_display_event_source(display_));
    al_register_event_source(queue_, al_get_timer_event_source(timer_));
    al_register_event_source(queue_, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer_);

    while(true)
    {
        al_wait_for_event(queue_, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (state_ == State::shoot)
                {
                    move_pawn();
                    clean_pawn();
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

                if (event.mouse.button == 1 && state_ == State::aim_)
                    add_pawn();
            
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:

                if (state_ == State::choose)
                    update_aim_center(event.mouse.x, event.mouse.y);
            
                else if (state_ == State::aim_)
                    update_aim_direction(event.mouse.x, event.mouse.y);
            
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue_))
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
    
    if (active_king_->contain(mouse_coordinate))
    {
        aim_.center(active_king_->center());
        aim_.show_reach_circle();
        state_ = State::aim_;
    }
    else
    {
        for (const auto &pawn : *active_pawns_)
        {
            if (pawn.contain(mouse_coordinate))
            {
                aim_.center(pawn.center());
                aim_.show_reach_circle();
                state_ = State::aim_;
            }
        }
    }
}

void Game::update_aim_direction(float x, float y)
{
    Vector mouse_coordinate = Vector(x, y);
    
    if (active_king_->contain(mouse_coordinate))
        aim_.center(active_king_->center());

    else
        for (const auto &pawn : *active_pawns_)
            if (pawn.contain(mouse_coordinate))
                aim_.center(pawn.center());

    aim_.update_direction(mouse_coordinate);
    aim_.show_direction_sign();
}

void Game::add_pawn()
{
    aim_.hide();

    active_pawns_->emplace_back(Pawn(
        aim_.center(),
        active_king_->color()
    ));

    Pawn::update_translation(aim_.center(), aim_.pawn_destination());
    Pawn::reset_translation_step_count();
    state_ = State::shoot;
}

void Game::move_pawn()
{
    active_pawns_->back().move();

    collision::response(vanishing_pawns_, active_pawns_->back(), *passive_pawns_);

    collision::response(active_pawns_->back(), *active_king_, [&](float t)
    {
        if (!active_king_->contain(aim_.center())) // when pawn doesn't come out of king
        {
            active_pawns_->back().retreat(1 - t);
            active_pawns_->back().stop();
        }
    });

    collision::response(active_pawns_->back(), *passive_king_, [&](float f)
    {
        Pawn::vanish_immediately(true);

        f = collision::circle_vs_circle(
            active_pawns_->back().shape(),
            passive_king_->king_shape(),
            active_pawns_->back().last_translation()
        );

        if (f <= 1)
            passive_king_->life_decrease_by(1);
    });

    collision::response(vanishing_pawns_, active_pawns_->back(), fence_);
}

void Game::clean_pawn()
{
    if (Pawn::vanish_immediately() && Pawn::finish_moving())
    {
        active_pawns_->pop_back();
        Pawn::vanish_immediately(false);
    }
    else if (vanishing_pawns_.empty() && Pawn::finish_moving())
    {
        std::swap(active_king_, passive_king_);
        std::swap(active_pawns_, passive_pawns_);

        state_ = State::choose;
        aim_.color(active_king_->color());
        // std::cout << "move pawn > choose and aim_\n";
    }

    for(auto it = vanishing_pawns_.begin(); it != vanishing_pawns_.end();)
    {
        if (!(*it)->color_equal_vanish())
        {
            (*it)->transform_color_to_vanish();
            ++it;
            continue;
        }

        if (*it >= &pawns_magenta_.front() && *it <= &pawns_magenta_.back())
        {
            pawns_magenta_.erase(pawns_magenta_.begin() + (*it - &pawns_magenta_.front()));
        }
        else if (*it >= &pawns_cyan_.front() && *it <= &pawns_cyan_.back())
        {
            pawns_cyan_.erase(pawns_cyan_.begin() + (*it - &pawns_cyan_.front()));
        }
    
        it = vanishing_pawns_.erase(it);
    }
}