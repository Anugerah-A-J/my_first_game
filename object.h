#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "geometry.h"
#include "param.h"
#pragma once

class Aim
{
public:
    Aim()
    :
        reach_circle_{0, 0, param::reach_radius, param::magenta, param::line_width},
        pawn_destination_{0, 0},
        direction_sign_{
            Vector(0, 0),
            Vector(0, 0),
            Vector(0, 0),
            param::magenta,
            param::line_width
        },
        reach_circle_is_visible_{false},
        direction_sign_is_visible_{false}
    {}

    void draw() const
    {
        if (reach_circle_is_visible_)
            reach_circle_.draw();

        if (direction_sign_is_visible_)
            direction_sign_.draw();
    }

    void center(const Vector& point) { reach_circle_.center(point); }
    const Vector& center() { return reach_circle_.center(); }

    const Vector& pawn_destination() const { return pawn_destination_; }

    void update_direction(const Vector& mouse_coordinate)
    {
        Vector unit = (mouse_coordinate - reach_circle_.center()).unit();

        pawn_destination_ = reach_circle_.center() - unit * reach_circle_.radius();
        
        direction_sign_.vertex_1(reach_circle_.center() + unit * param::unit_length);

        Vector temp = direction_sign_.vertex_1() + unit * param::unit_length;

        direction_sign_.vertex_2(temp + Matrix(0, 1, -1, 0) * unit * param::unit_length / param::sqrt_3);

        direction_sign_.vertex_3(temp + Matrix(0, -1, 1, 0) * unit * param::unit_length / param::sqrt_3);
    }

    void show_reach_circle() { reach_circle_is_visible_ = true; }
    void show_direction_sign() { direction_sign_is_visible_ = true; }
    void hide()
    {
        reach_circle_is_visible_ = false;
        direction_sign_is_visible_ = false;
    }
    void color(const ALLEGRO_COLOR& color)
    {
        reach_circle_.color(color);
        direction_sign_.color(color);
    }
private:
    Circle reach_circle_;
    Vector pawn_destination_;
    Triangle direction_sign_;
    bool reach_circle_is_visible_;
    bool direction_sign_is_visible_;
};

class Clipper
{
public:
    Clipper()
    :
        left_{
            0,
            0,
            2 * param::unit_length,
            param::window_height,
            param::black,
            0
        },
        top_{
            0,
            0,
            param::window_width,
            param::unit_length,
            param::black,
            0
        },
        right_{
            param::window_width - 2 * param::unit_length,
            0,
            2 * param::unit_length,
            param::window_height,
            param::black,
            0
        },
        bottom_{
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
        left_.draw();
        top_.draw();
        right_.draw();
        bottom_.draw();
    };
private:
    Rectangle left_;
    Rectangle top_;
    Rectangle right_;
    Rectangle bottom_;
};

class Fence
{
public:
    Fence()
    :
        shape_{
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
        shape_.draw();
    };

    const Rectangle& shape() const { return shape_; }
private:
    Rectangle shape_;
};