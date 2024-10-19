#include "Game.hpp"
#pragma once

void Game::update_aim()
{
    if (state != State::choose_and_aim || event.type != ALLEGRO_EVENT_MOUSE_AXES)
        return;

    Vector mouse_coordinate = Vector(event.mouse.x, event.mouse.y);
    
    if (king->contain(mouse_coordinate))
    {
        aim.shape_circle.center = king->shape_circle.center;
        aim.visible = true;
    }
    else
    {
        for (const auto &pawn : *pawns)
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