#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "Shapes.hpp"
#include "param.hpp"
#pragma once

struct Fence
{
    void draw() const
    {
        al_draw_rectangle(
            shape.start.x,
            shape.start.y,
            shape.end.x,
            shape.end.y,
            color,
            thickness
        );
    };

    Rectangle shape = Rectangle(
        2 * param::space,
        param::space,
        param::window_width - 4 * param::space,
        param::window_height - 2 * param::space
    );
    
    ALLEGRO_COLOR color = param::red;

    float thickness = param::line_width;
};