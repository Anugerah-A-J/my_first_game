#include "Shape.hpp"
#include <vector>
#pragma once

class Aim
{
public:
    Aim();
    void Draw() const;
    void Center(const Vector& point);
    const Vector& Center();
    const Vector& End_point() const;
    void Update_direction(const Vector& mouse_coordinate);
    void Show_reach_circle();
    void Show_direction_sign();
    void Hide();
    void Color(const ALLEGRO_COLOR& color);
    bool Reach_circle_is_visible() const;
    bool Direction_sign_is_visible() const;
private:
    Circle reach_circle;
    Vector end_point;
    Triangle direction_sign;
    ALLEGRO_COLOR color;
    float line_width;
    bool reach_circle_is_visible;
    bool direction_sign_is_visible;
};

class Clipper
{
public:
    Clipper(const Rectangle& map_fence_shape);
    void Draw() const;
private:
    Rectangle left;
    Rectangle top;
    Rectangle right;
    Rectangle bottom;
    ALLEGRO_COLOR color;
};

class Fence
{
public:
    Fence(const Vector& origin, const Vector& size);
    void Draw() const;
    const Vector& Origin() const;
    Vector Top_right() const;
    Vector Top_left() const;
    Vector Bottom_left() const;
    Vector Bottom_right() const;
    Vector Center() const;
    float Width() const;
    float Height() const;
    const Rectangle& Shape() const;
    // void Hurt(Player& player) const;
private:
    Rectangle shape;
    ALLEGRO_COLOR color;
    float line_width;
};

class Wall
{
public:
    Wall(const Vector& origin, const Vector& size);
    void Draw() const;
    const Rectangle& Shape() const;
    void Center(const Vector& point);
    Wall Mirror_x(const Vector& point) const;
    Wall Mirror_y(const Vector& point) const;
private:
    Rectangle shape;
};

// class Tree
// {
// public:
//     Tree(const Vector& center, float overall_diameter);
//     void Draw() const;
//     void Translate(const Vector& displacement);
//     Tree Mirror_x(const Vector& point) const;
//     Tree Mirror_y(const Vector& point) const;
//     // float Min_t(const Player& moving_pawn) const;
// private:
//     float diameter;
//     std::vector<Circle> shape;
//     Circle filler;
// };

// class X
// {
// public:
//     X(const Vector& origin, float size);
//     void Draw() const;
//     void Translate(const Vector& displacement);
//     // float Min_t(const Player& moving_pawn) const;
//     X Mirror_y(const Vector& point) const;
//     X Mirror_x(const Vector& point) const;
// private:
//     float size;
//     std::array<Line, 2> shape;
// };

// class Glass
// {
// public:
//     Glass(const Vector& start, const Vector& end);
//     void Draw() const;
//     const Line& Shape() const;
//     void Translate(const Vector& displacement);
//     Glass Mirror_y(const Vector& point) const;
//     Glass Mirror_x(const Vector& point) const;
// private:
//     Line shape;
// };

class Map
{
public:
    void Draw() const;
    virtual Vector Magenta_spawn_position() const = 0;
    virtual Vector Cyan_spawn_position() const = 0;
    Vector Magenta_lives_start_position() const;
    Vector Cyan_lives_start_position() const;
    const Rectangle& Fence_shape() const;
    const std::vector<Wall>& Get_wall() const;
    // void Reflect_and_hurt(Player* const player) const;
    // void Reflect(Player* const player) const;
    // void Hide(Player* const player) const;
    // void Obstruct(Player* const player) const;
protected:
    Map(const Vector& size);
    // Map(const Vector& size, float the_number_of_wall, float the_number_of_xs, float the_number_of_glass, float the_number_of_tree);
    Fence fence;
    Clipper clipper;
    std::vector<Wall> wall;
    // std::vector<X> xs;
    // std::vector<Glass> glass;
    // std::vector<Tree> tree;
};

class Map_1 : public Map
{
public:
    Map_1();
    Vector Magenta_spawn_position() const override;
    Vector Cyan_spawn_position() const override;
private:
    void Arrange_wall();
    // void Arrange_windows();
    // void Arrange_xs();
    // void Arrange_trees();
};
