#include "Shape.hpp"
#include "Param.hpp"
#include <array>
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
    Clipper(const Fence& fence);
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
    Fence();
    void Draw() const;
    const Vector& Origin() const;
    const Vector& Top_right() const;
    const Vector& Bottom_left() const;
    Vector Center() const;
    float Width() const;
    float Height() const;
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
private:
    Rectangle shape;
};

class Tree
{
public:
    Tree(const Vector& center, float overall_diameter);
    void Draw() const;
    void Translate(const Vector& displacement);
    Tree Mirror_x(const Vector& point) const;
    Tree Mirror_y(const Vector& point) const;
    float Min_t(const Pawn& moving_pawn) const;
private:
    float diameter;
    std::vector<Circle> shape;
    Circle filler;
};

class X
{
public:
    X(const Vector& origin, float size);
    void Draw() const;
    void Translate(const Vector& displacement);
    float Min_t(const Pawn& moving_pawn) const;
    X Mirror_y(const Vector& point) const;
    X Mirror_x(const Vector& point) const;
private:
    float size;
    std::array<Line, 2> shape;
};

class Window
{
public:
    Window(const Vector& start, const Vector& end);
    void Draw() const;
    const Line& Shape() const;
    void Translate(const Vector& displacement);
    Window Mirror_y(const Vector& point) const;
    Window Mirror_x(const Vector& point) const;
private:
    Line shape;
};

class Map
{
public:
    void Draw() const;
    void Wall_stop(Pawn& moving_pawn) const;
    void Tree_stop(Pawn& moving_pawn) const;
    void X_kill(Pawn& moving_pawn, std::set<Pawn *> &dying_pawns) const;
    void Window_only_shoot(Pawn& moving_pawn) const;
protected:
    Map(
        float the_number_of_walls,
        float the_number_of_windows,
        float the_number_of_xs,
        float the_number_of_trees
    );
    const Fence fence;
    std::vector<Wall> walls;
    std::vector<Window> windows;
    std::vector<X> xs;
    std::vector<Tree> trees;
};

class Map_1 : public Map
{
public:
    Map_1();
private:
    void Arrange_walls();
    void Arrange_windows();
    void Arrange_xs();
    void Arrange_trees();
};