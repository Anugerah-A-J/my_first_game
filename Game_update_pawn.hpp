#include "Game.hpp"
#pragma once

void Game::update_pawn()
{
    // if (state != State::move_pawn || event.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event.mouse.button != 1)
    if (state != State::move_pawn)
        return;

    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
    {
        /* code */
    }
    else if (event.type == ALLEGRO_EVENT_TIMER)
    {
        ;
    }
};