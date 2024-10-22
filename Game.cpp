#include "Game.hpp"
#include <iostream>
#include "Collision.hpp"

void Game::draw() const
{
    if (state != State::end)
    {
        al_clear_to_color(param::black);
        
        aim.draw();
        king_cyan.draw();
        king_magenta.draw();
        
        clipper.draw();
        fence.draw();

        for (const auto& pawn_magenta: pawns_magenta)
        {
            pawn_magenta.draw();
        }

        for (const auto& pawn_cyan: pawns_cyan)
        {
            pawn_cyan.draw();
        }
    }
};

void Game::run()
{
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    // ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(true)
    {
        al_wait_for_event(queue, &event);

        update_aim();
        update_pawn();

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // move_pawn(state);
                // kill_and_delete_pawns();
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                // if (event.mouse.button == 1)
                //     add_pawn(state);
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
};

void Game::update_aim()
{
    if (state != State::choose_and_aim || event.type != ALLEGRO_EVENT_MOUSE_AXES)
        return;

    Vector mouse_coordinate = Vector(event.mouse.x, event.mouse.y);
    
    if (active_king->contain(mouse_coordinate))
    {
        aim.shape_circle.center = active_king->shape_circle.center;
        aim.visible = true;
    }
    else
    {
        for (const auto &pawn : *active_pawns)
        {
            if (pawn.contain(mouse_coordinate))
            {
                aim.shape_circle.center = pawn.shape.center;
                aim.visible = true;
            }
        }
    }

    Vector v = mouse_coordinate - aim.shape_circle.center;
    Vector v_unit = v.unit();

    aim.end_point = aim.shape_circle.center - v_unit * aim.shape_circle.radius;
    
    aim.shape_triangle.vertex_1 = aim.shape_circle.center + v_unit * param::radius * 2;

    Vector temp = aim.shape_triangle.vertex_1 + v_unit * param::triangle_height;

    aim.shape_triangle.vertex_2 = temp + Matrix(0, 1, -1, 0) * v_unit * param::triangle_height / param::sqrt_3;

    aim.shape_triangle.vertex_3 = temp + Matrix(0, -1, 1, 0) * v_unit * param::triangle_height / param::sqrt_3;
};

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
            Collision::response(active_pawns->back(), *active_king, true, aim);
            Collision::response(active_pawns->back(), *passive_king, false, aim);
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