#include "Shape.hpp"
#include "Param.hpp"
#include <vector>
#include "Object.hpp"
#pragma once

class Player
{
protected:
    Player(const Vector& center, const ALLEGRO_COLOR& color);
public:
    void Draw() const;
    bool Contain(const Vector& point) const;
    bool Reach(const Vector& point) const;
    
    const Vector& Center() const;
    static void Update_translation(const Vector& start, const Vector& end);
    void Move();
    static bool Finish_moving();
    const ALLEGRO_COLOR& Color() const;

    void Update_life();
    // void Reflect(Player& enemy);
    // bool Dead();
    // void Reset_life();
    
    // const Circle& Shape() const;
    // Line Last_translation() const;
    // void Retreat(float compared_to_latest_translation);
    // static void Reset_translation_step_count();

    // int Life() const;
    // void Life_will_be_decreased();
    // void Decrease_life();
    // void Transform_color_to_vanish();
    // bool Color_equal_vanish();
    // const Circle& Shape() const;
    // void Vanish_immediately(bool value);
    // bool Vanish_immediately();
protected:
    Circle shape;
    ALLEGRO_COLOR color;
    int life;
    std::vector<Circle> life_shapes;
    bool decrease_life;
    inline static Translation translation;
};

class Player_magenta : public Player
{
public:
    Player_magenta(const Map& map);
};

class Player_cyan : public Player
{
public:
    Player_cyan(const Map& map);
};