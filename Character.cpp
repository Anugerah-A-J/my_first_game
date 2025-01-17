#include "Character.hpp"
#include "Collision.hpp"
#include "Param.hpp"
#include "Shape.hpp"
#include <algorithm>
#include <vector>

Player::Player(const Vector &center, const ALLEGRO_COLOR &color)
:
    shape{center, Param::unit_length / 2},
    color{color},
    life{Param::life},
    life_shapes{Param::life, shape},
    decrease_life{0},
    translation{shape.center}
{}

void Player::Draw() const
{
    shape.Draw(color);

    for (unsigned int i = 0; i < life; i++)
        life_shapes.at(i).Draw(color);
}

bool Player::Contain(const Vector &point) const
{
    return shape.Contain(point);
}

bool Player::Reach(const Vector &point) const
{
    Circle c {shape.center, Param::reach_radius};
    return c.Contain(point);
}

const Vector& Player::Center() const
{
    return shape.center;
}

void Player::Move()
{
    translation.Move(shape);
}

bool Player::Finish_moving()
{
    return translation.Finish();
}

void Player::Update_life()
{
    life -= decrease_life;
    decrease_life = 0;
}

bool Player::Dead()
{
    return life == 0;
}

const ALLEGRO_COLOR &Player::Color() const
{
    return color;
}

void Player::Reset_life()
{
    life = Param::life;
}

void Player::Update_translation(const Vector &end)
{
    translation.Reset_all(end);
}

void Player::Update_displacement()
{
    translation.Update_displacement();
}

void Player::Decrease_life()
{
    decrease_life--;
}

// void Player::Reset_translation_step_count()
// {
//     translation_step_count = 0;
// }

    // int Life() const { return life; }
    // void Life_will_be_decreased() { decrease_life = true; }

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

    // Pawn(float cx, float cy, const ALLEGRO_COLOR& color)
    //     : shape{Vector(cx, cy), Param::unit_length / 2}
    //     , color{color}
    // {}

    // Pawn(const Vector& center, const ALLEGRO_COLOR& color)
    //     : shape{center, Param::unit_length / 2}
    //     , color{color}
    // {}

    // bool Contain(const Vector& point) const { return shape.Contain(point); }

    // static void Stop() { translation_step_count = Param::translation_step; }

    // void Transform_color_to_vanish()
    // {
    //     Transform_color(color, Param::vanish, Param::color_transformation_ratio);
    // }

    // bool Color_equal_vanish()
    // {
    //     if (Equal(color, Param::vanish, 0.05f))
    //         return true;

    //     return false;
    // }


std::shared_ptr<Collision> Player::Inside(const Rectangle& rectangle)
{
    return std::make_shared<Circle_inside_rectangle>(
        shape,
        translation,
        rectangle
    );
}

std::shared_ptr<Collision> Player::Between(Player& passive_player)
{
    return std::make_shared<Circle_outside_circle>(
        shape,
        translation,
        passive_player.shape,
        passive_player.translation
    );
}

std::shared_ptr<Collision> Player::Between(const Rectangle& rectangle)
{
    return std::make_shared<Circle_outside_rectangle>(
        shape,
        translation,
        rectangle
    );
}


    // Vector Center() const { return shape.Center(); }

    // static void Vanish_immediately(bool value) { vanish_immediately = value; }
    // static bool Vanish_immediately() { return vanish_immediately; }

    // void Kill(std::vector<Pawn> &pawns, std::set<Pawn *> &dying_pawns) const
    // {
    //     for (auto& pawn : pawns) {
    //         if (Collision::Circle_vs_circle(shape, pawn.Shape(), Last_translation()) == 2)
    //             continue;

    //         dying_pawns.insert(&pawn);
    //     }
    // }

    // void Hurt(King& king) const
    // {
    //     float t = Collision::Circle_vs_rectangle(shape, king.Throne_shape(), Last_translation());

    //     if (t != 2)
    //         Pawn::Vanish_immediately(true);

    //     t = Collision::Circle_vs_circle(shape, king.King_shape(), Last_translation());

    //     if (t <= 1)
    //         king.Life_will_be_decreased();
    // }

    // void Stopped_by(const King& king, const Vector& moving_pawn_spawn_position)
    // {
    //     float t = Collision::Circle_vs_rectangle(shape, king.Throne_shape(), Last_translation());

    //     if (t == 2)
    //         return;

    //     if (!king.Contain(moving_pawn_spawn_position)) // when pawn doesn't come out of king
    //     {
    //         Retreat(1 - t);
    //         Stop();
    //     }
    // }

// Line Player::Last_translation() const
// {
//     return Line(shape.Center() - translation, shape.Center());
// }

// const Circle &Player::Shape() const
// {
//     return shape;
// }

Player_magenta::Player_magenta(const Map& map)
:
    Player{map.Magenta_spawn_position(), Param::magenta}
{
    Circle c = shape;
    c.center = map.Magenta_lives_start_position();

    std::fill(life_shapes.begin(), life_shapes.end(), c);

    // 0 -> 0
    // 1 -> 2u
    // 2 -> 4u
    for(int i = 0; i < Param::life; i++)
        life_shapes.at(i).Translate(Vector(0, i * 2 * Param::unit_length));
}

Player_cyan::Player_cyan(const Map& map)
:
    Player{map.Cyan_spawn_position(), Param::cyan}
{
    Circle c = shape;
    c.center = map.Cyan_lives_start_position();

    std::fill(life_shapes.begin(), life_shapes.end(), c);

    // 0 -> 0
    // 1 -> 2u
    // 2 -> 4u
    for(int i = 0; i < Param::life; i++)
        life_shapes.at(i).Translate(Vector(0, i * 2 * Param::unit_length));
}
