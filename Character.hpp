#include "Shape.hpp"
#include <vector>
#include "Object.hpp"
#include "Collision.hpp"
#include <memory>
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
    void Update_translation(const Vector& end);
    void Update_displacement();
    void Move();
    bool Finish_moving();
    const ALLEGRO_COLOR& Color() const;

    void Update_life();
    bool Dead();

    std::shared_ptr<Collision> Inside(const Rectangle& rectangle);
    std::shared_ptr<Collision> Between(Player& passive_player);
    std::shared_ptr<Collision> Between(const Rectangle& rectangle);
    
    // Line Last_translation() const;
    // static void Reset_translation_step_count();

    // int Life() const;
    // void Life_will_be_decreased();
    void Decrease_life();
    // void Transform_color_to_vanish();
    // bool Color_equal_vanish();
    // const Circle& Shape() const;
    // void Vanish_immediately(bool value);
    // bool Vanish_immediately();
protected:
    Circle shape;
    ALLEGRO_COLOR color;
    unsigned int life;
    std::vector<Circle> life_shapes;
    int decrease_life;
    Translation translation;
};

class Player_magenta : public Player
{
public:
    Player_magenta(const Map& map);
    void Reset_all(const Map& map);
};

class Player_cyan : public Player
{
public:
    Player_cyan(const Map& map);
    void Reset_all(const Map& map);
};
