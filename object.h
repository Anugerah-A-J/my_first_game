#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "geometry.h"
#include "param.h"
#pragma once

class Aim
{
public:
    Aim():
        Reach_circle{0, 0, param::reach_radius, param::magenta, param::line_width},
        Pawn_destination{0, 0},
        Direction_sign{Vector(0, 0), Vector(0, 0), Vector(0, 0), param::magenta, param::line_width},
        Visible{false}
    {};
    void draw() const
    {
        if (!Visible)
            return;
        
        Reach_circle.draw();
        Direction_sign.draw();
    };
private:
    Circle Reach_circle;
    Vector Pawn_destination;
    Triangle Direction_sign;
    bool Visible;
};

class Clipper
{
public:
    Clipper():
        Left{
            0,
            0,
            2 * param::unit_length,
            param::window_height,
            param::black,
            0
        },
        Top{
            0,
            0,
            param::window_width,
            param::unit_length,
            param::black,
            0
        },
        Right{
            param::window_width - 2 * param::unit_length,
            0,
            2 * param::unit_length,
            param::window_height,
            param::black,
            0
        },
        Bottom{
            0,
            param::window_height - param::unit_length,
            param::window_width,
            param::unit_length,
            param::black,
            0
        }
    {};

    void draw() const
    {
        Left.draw_filled();
        Top.draw_filled();
        Right.draw_filled();
        Bottom.draw_filled();
    };
private:
    Rectangle Left;
    Rectangle Top;
    Rectangle Right;
    Rectangle Bottom;
};

class Fence
{
public:
    Fence():
        Shape{
            2 * param::unit_length,
            param::unit_length,
            param::window_width - 4 * param::unit_length,
            param::window_height - 2 * param::unit_length,
            param::red,
            param::line_width
        }
    {};
    void draw() const
    {
        Shape.draw();
    };
private:
    Rectangle Shape;
};