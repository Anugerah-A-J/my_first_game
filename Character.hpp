#include "Shape.hpp"
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
    
    // The functions below are needed to move player
    const Vector& Center() const;
    void Update_translation(const Vector& start, const Vector& end);
    void Move(const Map& map, Player* const enemy);
    bool Finish_moving();
    const ALLEGRO_COLOR& Color() const;

    // The functions below are needed to reflect and hurt player
    void Update_life();
    // void Reflect(Player& enemy);
    // bool Dead();
    // void Reset_life();
    
    // const Circle& Shape() const;
    // Line Last_translation() const;
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
    Translation translation;
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
