#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "Shapes.hpp"
#include "param.hpp"
#pragma once

struct Clipper
{
    void draw() const
    {
        al_draw_filled_rectangle(
            left.start.x,
            left.start.y,
            left.end.x,
            left.end.y,
            color
        );

        al_draw_filled_rectangle(
            top.start.x,
            top.start.y,
            top.end.x,
            top.end.y,
            color
        );

        al_draw_filled_rectangle(
            right.start.x,
            right.start.y,
            right.end.x,
            right.end.y,
            color
        );

        al_draw_filled_rectangle(
            bottom.start.x,
            bottom.start.y,
            bottom.end.x,
            bottom.end.y,
            color
        );
    };

    Rectangle left = Rectangle(
        0,
        0,
        2 * param::space,
        param::window_height
    );
    
    Rectangle top = Rectangle(
        0,
        0,
        param::window_width,
        param::space
    );
    
    Rectangle right = Rectangle(
        param::window_width - 2 * param::space,
        0,
        2 * param::space,
        param::window_height
    );
    
    Rectangle bottom = Rectangle(
        0,
        param::window_height - param::space,
        param::window_width,
        param::space
    );
    
    ALLEGRO_COLOR color = param::black;
};