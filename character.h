#include "geometry.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "param.h"
#pragma once

struct King
{
    Circle shape_circle;
    Rectangle shape_rectangle;
    Vector live;
    ALLEGRO_COLOR color;
    float thickness;
    int lives;

    King(const Circle& c, const Rectangle& r, const Vector& live, const ALLEGRO_COLOR& color, float thickness)
    :
        shape_circle{c},
        shape_rectangle{r},
        live{live},
        color{color},
        thickness{thickness},
        lives{param::lives}
    {};

    void draw() const
    {
        al_draw_rectangle(
            shape_rectangle.start.x,
            shape_rectangle.start.y,
            shape_rectangle.end.x,
            shape_rectangle.end.y,
            color,
            thickness
        );

        al_draw_filled_circle(
            shape_circle.center.x,
            shape_circle.center.y,
            shape_circle.radius,
            color
        );
    };

    void draw_lives() const
    {
        if (lives >= 1)
            al_draw_filled_circle(
                live.x,
                live.y + shape_rectangle.size.y,
                shape_circle.radius / 2,
                color
            );

        if (lives >= 2)
            al_draw_filled_circle(
                live.x,
                live.y + shape_rectangle.size.y / 2,
                shape_circle.radius / 2,
                color
            );

        if (lives >= 3)
            al_draw_filled_circle(
                live.x,
                live.y,
                shape_circle.radius / 2,
                color
            );
    };

    bool contain(const Vector& v) const
    {
        return (v - shape_circle.center).magsq <= shape_circle.radius * shape_circle.radius;
    };
};

struct King_magenta:
    public King
{
    King_magenta()
    :
        King{
            Circle(
                param::window_width - param::space * 3 - param::radius,
                param::window_height / 2,
                param::radius
            ),
            Rectangle(
                param::window_width - (param::space * 2 + param::radius) * 2,
                param::window_height / 2 - param::radius - param::space,
                param::radius * 2 + param::space * 2,
                param::radius * 2 + param::space * 2
            ),
            Vector(
                param::window_width - param::space,
                param::window_height / 2 - param::radius - param::space
            ),
            param::magenta,
            param::line_width
        }
    {};
};

struct King_cyan:
    public King
{
    King_cyan()
    :
        King{
            Circle(
                param::space * 3 + param::radius,
                param::window_height / 2,
                param::radius
            ),
            Rectangle(
                param::space * 2,
                param::window_height / 2 - param::radius - param::space,
                param::radius * 2 + param::space * 2,
                param::radius * 2 + param::space * 2
            ),
            Vector(
                param::space,
                param::window_height / 2 - param::radius - param::space
            ),
            param::cyan,
            param::line_width
        }
    {};
};

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