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
        king_shape_{king_shape},
        throne_shape_{throne_shape},
        life_{param::life},
        life_shapes_{king_shape, king_shape, king_shape}
    {
        for (auto& life_shape: life_shapes_)
        {
            life_shape.scale(0.5);
            life_shape.center(last_life_position);
        }

        for (auto it = life_shapes_.begin() + 1; it != life_shapes_.end(); ++it)
            (*it).translate(0, -throne_shape_.size().Y() / 2 * (it - life_shapes_.begin()));
    };

    void draw() const
    {
        king_shape_.draw();
        throne_shape_.draw();
    };

    void draw_life() const
    {
        for (auto it = life_shapes_.begin(); it != life_shapes_.begin() + life_; ++it)
            (*it).draw();
    }

    bool contain(const Vector& point) const
    {
        return king_shape_.contain(point);
    }

    Vector center() const
    {
        return king_shape_.center();
    }

    const ALLEGRO_COLOR& color() const { return king_shape_.color(); }

    const Circle& king_shape() const { return king_shape_; }
    const Rectangle& throne_shape() const { return throne_shape_; }

    int life() const { return life_; }
    void life_decrease_by(int value) { life_ -= value; }
private:
    Circle king_shape_;
    Rectangle throne_shape_;
    int life_;
    std::vector<Circle> life_shapes_;
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
        shape_{cx, cy, param::unit_length / 2, color, 0}
        // ,Visible{true}
    {}

    Pawn(const Vector& center, const ALLEGRO_COLOR& color)
    :
        shape_{center, param::unit_length / 2, color, 0}
        // ,Visible{true}
    {}

    void draw() const
    {
        // if (!Visible)
        //     return;

        shape_.draw();
    }

    bool contain(const Vector& point) const
    {
        return shape_.contain(point);
    }

    static void update_translation(const Vector& start, const Vector& end)
    {
        translation_ = (end - start) / param::unit_length;
    }

    static void reset_translation_step_count()
    {
        translation_step_count_ = 0;
    }

    static void stop()
    {
        translation_step_count_ = param::translation_step;
    }

    void move()
    {
        if (translation_step_count_ == param::translation_step)
            return;

        translation_step_count_ ++;

        shape_.translate(translation_);
    }

    static bool finish_moving() { return translation_step_count_ == param::translation_step; }

    void retreat(float compared_to_latest_translation)
    {
        shape_.translate(-compared_to_latest_translation * translation_);
    }

    void transform_color_to_vanish()
    {
        shape_.transform_color_to(param::vanish, param::color_transformation_ratio);
    };

    bool color_equal_vanish()
    {
        if(equal(shape_.color(), param::vanish, 0.05f))
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
            shape_.center() - translation_,
            shape_.center()
        );
    }

    Vector center() const { return shape_.center(); }

    static void vanish_immediately(bool value) { vanish_immediately_ = value; }
    static bool vanish_immediately() { return vanish_immediately_; }

    const Circle& shape() const { return shape_; }
private:
    inline static unsigned int translation_step_count_ = 0;
    inline static Vector translation_ = Vector(0, 0);
    inline static bool vanish_immediately_ = false;
    Circle shape_;
    // bool Visible;
};