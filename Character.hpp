#include "Shape.hpp"
#include "Param.hpp"
#include <vector>
#pragma once

class Player
{
public:
    Player(const Vector& center, const ALLEGRO_COLOR& color);
    void Draw() const;
    bool Contain(const Vector& point) const;
    bool Reach(const Vector& point) const;
    Vector Center() const;
    void Move();
    void Reflect(const Player& enemy) const;
    static bool Finish_moving();
    void Update_life();
    bool Dead();
    const ALLEGRO_COLOR& Color() const;
    void Reset_life();
    static void Update_translation(const Vector& start, const Vector& end);
    static void Reset_translation_step_count();

    // int Life() const;
    // void Life_will_be_decreased();
    // void Decrease_life();
    // void Stop();
    // void Retreat(float compared_to_latest_translation);
    // void Transform_color_to_vanish();
    // bool Color_equal_vanish();
    // Line Last_translation() const;
    // const Circle& Shape() const;
    // void Vanish_immediately(bool value);
    // bool Vanish_immediately();
private:
    Circle shape;
    ALLEGRO_COLOR color;
    int life;
    std::vector<Circle> life_shapes;
    bool decrease_life;
    inline static unsigned int translation_step_count = 0;
    inline static Vector translation = Vector(0, 0);
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