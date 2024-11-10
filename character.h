#include "geometry.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "param.h"
#include <vector>
#pragma once

class King
{
public:
    King(const Circle& king_shape, const Rectangle& throne_shape, const Vector& last_life_position)
    :
        King_shape{king_shape},
        Throne_shape{throne_shape},
        Life{param::life},
        Life_shapes{king_shape, king_shape, king_shape}
    {
        for (auto& life_shape: Life_shapes)
        {
            life_shape.scale(1/2);
            life_shape.center(last_life_position);
        }

        for (auto it = Life_shapes.begin() + 1; it != Life_shapes.end(); ++it)
            (*it).translate(0, -Throne_shape.size().y() * (it - Life_shapes.begin()));
    };

    void draw() const
    {
        King_shape.draw();
        Throne_shape.draw();
    };

    void draw_life() const
    {
        for (auto it = Life_shapes.begin(); it != Life_shapes.begin() + Life; ++it)
            (*it).draw();
    }

    bool contain(const Vector& point) const
    {
        return (point - King_shape.center()).magsq() <= King_shape.radius() * King_shape.radius();
    }

    Vector center() const
    {
        return King_shape.center();
    }

    const ALLEGRO_COLOR& color() const { return King_shape.color(); }

    const Circle& king_shape() const { return King_shape; }
    const Rectangle& throne_shape() const { return Throne_shape; }

    int life() const { return Life; }
    void life_decrease_by(int value) { Life -= value; }
private:
    Circle King_shape;
    Rectangle Throne_shape;
    int Life;
    std::vector<Circle> Life_shapes;
};

class King_magenta
:
    public King
{
public:
    King_magenta()
    :
        King{
            Circle(
                param::window_width - param::unit_length * 3.5,
                param::window_height / 2,
                param::unit_length / 2,
                param::magenta,
                0
            ),
            Rectangle(
                param::window_width - param::unit_length * 5,
                param::window_height / 2 - param::unit_length * 1.5,
                param::unit_length * 3,
                param::unit_length * 3,
                param::magenta,
                param::line_width
            ),
            Vector(
                param::window_width - param::unit_length,
                param::window_height / 2 + param::unit_length * 1.5
            )
        }
    {};
};

class King_cyan
:
    public King
{
public:
    King_cyan()
    :
        King{
            Circle(
                param::unit_length * 3.5,
                param::window_height / 2,
                param::unit_length / 2,
                param::cyan,
                0
            ),
            Rectangle(
                param::unit_length * 2,
                param::window_height / 2 - param::unit_length * 1.5,
                param::unit_length * 3,
                param::unit_length * 3,
                param::cyan,
                param::line_width
            ),
            Vector(
                param::unit_length,
                param::window_height / 2 + param::unit_length * 1.5
            )
        }
    {};
};

class Pawn
{
public:
    Pawn(float cx, float cy, const ALLEGRO_COLOR& color)
    :
        Shape{cx, cy, param::unit_length, color, 0}
        // ,Visible{true}
    {}

    Pawn(const Vector& center, const ALLEGRO_COLOR& color)
    :
        Shape{center, param::unit_length, color, 0}
        // ,Visible{true}
    {}

    void draw() const
    {
        // if (!Visible)
        //     return;

        Shape.draw();
    }

    bool contain(const Vector& point) const
    {
        return (point - Shape.center()).magsq() <= Shape.radius() * Shape.radius();
    }

    static void update_translation(const Vector& start, const Vector& end)
    {
        Translation = (end - start) / param::unit_length;
    }

    static void reset_translation_step_count()
    {
        Translation_step_count = 0;
    }

    static void stop()
    {
        Translation_step_count = param::translation_step;
    }

    void move()
    {
        if (Translation_step_count == param::translation_step)
            return;

        Translation_step_count ++;

        Shape.translate(Translation);
    }

    static bool finish_moving() { return Translation_step_count == param::translation_step; }

    void retreat(float compared_to_latest_translation)
    {
        Shape.translate(-compared_to_latest_translation * Translation);
    }

    void transform_color_to_vanish()
    {
        Shape.transform_color_to(param::vanish, param::color_transformation_ratio);
    };

    bool color_equal_vanish()
    {
        if(equal(Shape.color(), param::vanish, 0.05f))
            return true;

        return false;
    };

    // void hide()
    // {
    //     Visible = false;
    // }

    Line last_translation() const
    {
        return Line(
            Shape.center() - Translation,
            Shape.center()
        );
    }

    Vector center() const { return Shape.center(); }

    static void vanish_immediately(bool value) { Vanish_immediately = value; }
    static bool vanish_immediately() { return Vanish_immediately; }

    const Circle& shape() const { return Shape; }
private:
    inline static unsigned int Translation_step_count = 0;
    inline static Vector Translation = Vector(0, 0);
    inline static bool Vanish_immediately = false;
    Circle Shape;
    // bool Visible;
};