#pragma once
#include <allegro5/color.h>
#include "Shapes.hpp"
#include "param.hpp"
#include <allegro5/allegro_primitives.h>

struct Pawn
{
    inline static unsigned int move_step_count = param::move_step;
    inline static Vector move_step_vector = Vector(0, 0);
    inline static bool dead_without_dying = false;

    Circle shape;
    ALLEGRO_COLOR color;
    
    Pawn(float cx, float cy, const ALLEGRO_COLOR& color)
    :
        shape{cx, cy, param::radius},
        color{color}
    {};

    void draw() const
    {
        al_draw_filled_circle(
            shape.center.x,
            shape.center.y,
            shape.radius,
            color
        );
    };

    bool contain(const Vector& v) const
    {
        return (v - shape.center).magsq <= shape.radius * shape.radius;
    };

    static void update_move_step_vector(const Vector& start, const Vector& end)
    {
        move_step_vector = (end - start) / param::move_step;
    };

    static void reset_move_step_count()
    {
        move_step_count = 0;
    };

    static void stop()
    {
        move_step_count = param::move_step;
    }

    void move()
    {
        move_step_count ++;
        shape.center += move_step_vector;
    };

    void retreat(float f)
    {
        shape.center -= f * move_step_vector;
    };

    void die()
    {
        color.r = (param::dead_color.r + color.r) * param::color_transformation_ratio;
        color.g = (param::dead_color.g + color.g) * param::color_transformation_ratio;
        color.b = (param::dead_color.b + color.b) * param::color_transformation_ratio;
        color.a = (param::dead_color.a + color.a) * param::color_transformation_ratio;
    };

    bool is_dead()
    {
        if(
            equal(color.r, param::dead_color.r, 0.05f) &&
            equal(color.g, param::dead_color.g, 0.05f) &&
            equal(color.b, param::dead_color.b, 0.05f) &&
            equal(color.a, param::dead_color.a, 0.05f)
        ){
            color.r = param::dead_color.r;
            color.g = param::dead_color.g;
            color.b = param::dead_color.b;
            color.a = param::dead_color.a;
            return true;
        }

        return false;
    };

    Line move_step_line_segment() const
    {
        return Line(
            shape.center - move_step_vector,
            shape.center
        );
    }
};