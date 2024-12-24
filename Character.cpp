#include "collision.hpp"
#include "Shape.hpp"
#include "Param.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <set>
#include <vector>
#pragma once

class King
{
public:
    King(const Circle& king_shape, const Rectangle& throne_shape, const ALLEGRO_COLOR& color, float line_width, const Vector& last_life_position)
    :
		king_shape{king_shape},
		throne_shape{throne_shape},
		color{color},
		line_width{line_width},
		life{Param::life},
		life_shapes{king_shape, king_shape, king_shape},
		decrease_life{false}
    {
        for (auto& life_shape : life_shapes) {
            life_shape.Scale(0.5);
            life_shape.Center(last_life_position);
        }

        for (auto it = life_shapes.begin() + 1; it != life_shapes.end(); ++it)
            (*it).Translate(Vector(0, -throne_shape.Size().Y() / 2 * (it - life_shapes.begin())));
    }

    void Draw() const
    {
        king_shape.Draw(color);
        throne_shape.Draw(color, line_width);
    }

    void Draw_life() const
    {
        for (auto it = life_shapes.begin(); it != life_shapes.begin() + life; ++it)
            (*it).Draw(color);
    }

    bool Contain(const Vector& point) const { return king_shape.Contain(point); }

    Vector Center() const { return king_shape.Center(); }

    const ALLEGRO_COLOR& Color() const { return color; }

    const Circle& King_shape() const { return king_shape; }
    const Rectangle& Throne_shape() const { return throne_shape; }
    int Life() const { return life; }
    void Life_will_be_decreased() { decrease_life = true; }
    void Update_life()
    {
        if (!decrease_life)
            return;

        life--;
        decrease_life = false;
    }
    void Reset_life() { life = Param::life; }

    // void Stops(Pawn& moving_pawn, const Vector& moving_pawn_spawn_position) const
    // {
    //     float t = collision::Circle_vs_rectangle(moving_pawn.Shape(), throne_shape, moving_pawn.Last_translation());

    //     if (t == 2)
    //         return;

    //     if (!Contain(moving_pawn_spawn_position)) // when pawn doesn't come out of king
    //     {
    //         moving_pawn.Retreat(1 - t);
    //         moving_pawn.Stop();
    //     }
    // }
private:
    Circle king_shape;
    Rectangle throne_shape;
    ALLEGRO_COLOR color;
    float line_width;
    int life;
    std::vector<Circle> life_shapes;
    bool decrease_life;
};

class King_magenta : public King
{
public:
    King_magenta()
    :
        King{
            Circle(
                Vector(
                    Param::window_width - Param::unit_length * 3.5,
                    Param::window_height / 2
                ),
                Param::unit_length / 2
            ),
            Rectangle(
                Vector(
                    Param::window_width - Param::unit_length * 5,
                    Param::window_height / 2 - Param::unit_length * 1.5
                ),
                Vector(
                    Param::unit_length * 3,
                    Param::unit_length * 
                3)
            ),
            Param::magenta,
            Param::line_width,
            Vector(
                Param::window_width - Param::unit_length,
                Param::window_height / 2 + Param::unit_length * 1.5
            )
        }
    {};
};

class King_cyan : public King
{
public:
    King_cyan()
    :
        King{
            Circle(
                Vector(Param::unit_length * 3.5, Param::window_height / 2),
                Param::unit_length / 2
            ),
            Rectangle(
                Vector(Param::unit_length * 2, Param::window_height / 2 - Param::unit_length * 1.5),
                Vector(Param::unit_length * 3, Param::unit_length * 3)
            ),
            Param::cyan,
            Param::line_width,
            Vector(Param::unit_length, Param::window_height / 2 + Param::unit_length * 1.5)
        }
    {};
};

class Pawn
{
public:
    Pawn(float cx, float cy, const ALLEGRO_COLOR& color)
        : shape{Vector(cx, cy), Param::unit_length / 2}
        , color{color}
    {}

    Pawn(const Vector& center, const ALLEGRO_COLOR& color)
        : shape{center, Param::unit_length / 2}
        , color{color}
    {}

    void Draw() const { shape.Draw(color); }

    bool Contain(const Vector& point) const { return shape.Contain(point); }

    static void Update_translation(const Vector& start, const Vector& end)
    {
        translation = (end - start) / Param::translation_step;
    }

    static void Reset_translation_step_count() { translation_step_count = 0; }

    static void Stop() { translation_step_count = Param::translation_step; }

    void Move()
    {
        if (translation_step_count == Param::translation_step)
            return;

        translation_step_count++;

        shape.Translate(translation);
    }

    static bool Finish_moving() { return translation_step_count == Param::translation_step; }

    void Retreat(float compared_to_latest_translation)
    {
        shape.Translate(-compared_to_latest_translation * translation);
    }

    void Transform_color_to_vanish()
    {
        Transform_color(color, Param::vanish, Param::color_transformation_ratio);
    }

    bool Color_equal_vanish()
    {
        if (Equal(color, Param::vanish, 0.05f))
            return true;

        return false;
    }

    Line Last_translation() const { return Line(shape.Center() - translation, shape.Center()); }

    const Circle& Shape() const { return shape; }

    Vector Center() const { return shape.Center(); }

    static void Vanish_immediately(bool value) { vanish_immediately = value; }
    static bool Vanish_immediately() { return vanish_immediately; }

    void Kill(std::vector<Pawn> &pawns, std::set<Pawn *> &dying_pawns) const
    {
        for (auto& pawn : pawns) {
            if (collision::Circle_vs_circle(shape, pawn.Shape(), Last_translation()) == 2)
                continue;

            dying_pawns.insert(&pawn);
        }
    }

    void Hurt(King& king) const
    {
        float t = collision::Circle_vs_rectangle(shape, king.Throne_shape(), Last_translation());

        if (t != 2)
            Pawn::Vanish_immediately(true);

        t = collision::Circle_vs_circle(shape, king.King_shape(), Last_translation());

        if (t <= 1)
            king.Life_will_be_decreased();
    }

    void Stopped_by(const King& king, const Vector& moving_pawn_spawn_position)
    {
        float t = collision::Circle_vs_rectangle(shape, king.Throne_shape(), Last_translation());

        if (t == 2)
            return;

        if (!king.Contain(moving_pawn_spawn_position)) // when pawn doesn't come out of king
        {
            Retreat(1 - t);
            Stop();
        }
    }

private:
    inline static unsigned int translation_step_count = 0;
    inline static Vector translation = Vector(0, 0);
    inline static bool vanish_immediately = false;
    Circle shape;
    ALLEGRO_COLOR color;
};
