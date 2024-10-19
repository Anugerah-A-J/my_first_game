#include "Game.hpp"
#include "Collision.hpp"
#include <iostream>
#pragma once

void Game::update_pawn()
{
    if (
        state == State::choose_and_aim &&
        aim.visible &&
        event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
        event.mouse.button == 1
    ){
        aim.visible = false;

        active_pawns->emplace_back(
            Pawn(
                aim.shape_circle.center.x,
                aim.shape_circle.center.y,
                active_king->color
            )
        );

        Pawn::update_move_step_vector(aim.shape_circle.center, aim.end_point);
        Pawn::reset_move_step_count();
        state = State::move_pawn;
        std::cout << "choose and aim > move pawn\n";
    }
    else if (state == State::move_pawn && event.type == ALLEGRO_EVENT_TIMER)
    {
        if (Pawn::move_step_count != param::move_step && !active_pawns->empty())
        {
            active_pawns->back().move();

            Collision::response(dying_pawns, active_pawns->back(), *passive_pawns);
            // Collision::response(active_pawns->back(), *passive_king);
            Collision::response(dying_pawns, active_pawns->back(), fence);
        }
        else if (Pawn::dead_without_dying && !active_pawns->empty())
        {
            active_pawns->pop_back();
            Pawn::dead_without_dying = false;
        }
        else if (dying_pawns.empty())
        {
            std::swap(active_king, passive_king);
            std::swap(active_pawns, passive_pawns);

            state = State::choose_and_aim;
            aim.color = active_king->color;
            std::cout << "move pawn > choose and aim\n";
        }

        for(auto it = dying_pawns.begin(); it != dying_pawns.end();)
        {
            if (!(*it)->is_dead())
            {
                (*it)->die();
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
        
            it = dying_pawns.erase(it);
        }
    }
};