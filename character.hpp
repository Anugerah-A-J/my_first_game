#include "Shape.hpp"
#include "Param.hpp"
#pragma once

class Player
{
public:
    Player(const Vector& center, const ALLEGRO_COLOR& color);
    void Draw() const;
    void Draw_life() const;
    Vector Center() const;
    const ALLEGRO_COLOR& Color() const;
    int Life() const;
    void Life_will_be_decreased();
    void Update_life();
    void Reset_life();
    void Update_translation(const Vector& start, const Vector& end);
    void Reset_translation_step_count();
    void Stop();
    void Move();
    bool Finish_moving();
    void Retreat(float compared_to_latest_translation);
    void Transform_color_to_vanish();
    bool Color_equal_vanish();
    Line Last_translation() const;
    const Circle& Shape() const;
    void Vanish_immediately(bool value);
    bool Vanish_immediately();
    void Hurt(std::vector<Pawn> &pawns, std::set<Pawn *> &dying_pawns) const;
private:
    Circle shape;
    ALLEGRO_COLOR color;
    int life;
    std::vector<Circle> life_shapes;
    bool decrease_life;
    unsigned int translation_step_count = 0;
    Vector translation = Vector(0, 0);
    bool vanish_immediately = false;
};

class Player_magenta : public Player
{
public:
    Player_magenta();
};

class Player_cyan : public Player
{
public:
    Player_cyan();
};