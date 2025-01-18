#include <allegro5/allegro_primitives.h>
#include <iostream>
#pragma once

void Println();

template <typename T>
void Println(const T& t)
{
    std::cout << t << '\n';
}

template <typename First, typename... Rest>
void Println(const First& first, const Rest&... rest)
{
    std::cout << first << ' ';
    Println(rest...); // recursive call using pack expansion syntax
}

bool Equal(float f1, float f2, float margin);

bool Equal(const ALLEGRO_COLOR& color_1, const ALLEGRO_COLOR& color_2, float margin);

void Transform_color(ALLEGRO_COLOR& changed_color, const ALLEGRO_COLOR& target_color, float color_transformation_ratio);

float Average(float f1, float f2);

float Square(float f);

class Vector
{
public:
    float x;
    float y;
    Vector(float x, float y);
    Vector operator-() const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(float f) const;
    Vector operator/(float f) const;
    void operator*=(float f);
    void operator/=(float f);
    void operator+=(const Vector& v);
    void operator-=(const Vector& v);
    bool operator==(const Vector& v) const;
    bool operator!=(const Vector& v) const;
    Vector Swap() const;
    Vector Unit() const;
    Vector Abs() const;
    static float Dot(const Vector& v1, const Vector& v2);
    float Magsq() const;
};

Vector operator*(float f, const Vector& v);

// template<typename T>
// T Sum(const std::vector<T>& ts)
// {
//     T out = ts.front();
//
//     for (unsigned int i = 1; i != ts.size(); i++)
//         out += ts.at(i);
//
//     return out;
// };

class Matrix
{
public:
    Vector row_1;
    Vector row_2;
    Matrix(float f1, float f2, float f3, float f4);
};

Vector operator*(const Matrix& m, const Vector& v);

class Line
{
public:
    Vector start;
    Vector end;
    Line(const Vector& start, const Vector& end);
    void Translate(const Vector& displacement);
    float Length() const;
    void Draw(const ALLEGRO_COLOR& color, float line_width) const;
    Line Mirror_x(const Vector& point) const;
    Line Mirror_y(const Vector& point) const;
    Vector Center() const;
    void Center(const Vector& point);
    Vector Direction() const;
};

class Rectangle
{
public:
    Vector origin;
    Rectangle(const Vector& origin, const Vector& size);
    void Draw(const ALLEGRO_COLOR& color) const;
    void Draw(const ALLEGRO_COLOR& line_color, float line_width) const;
    void Translate(const Vector& displacement);
    Vector Top_left() const;
    Vector Top_right() const;
    Vector Bottom_right() const;
    Vector Bottom_left() const;
    Line Top() const;
    Line Right() const;
    Line Bottom() const;
    Line Left() const;
    bool Contain(const Vector& point) const;
    const Vector& Size() const;
    void Add_size_by(const Vector& value);
    float Width() const;
    void Width(float val);
    float Height() const;
    void Height(float val);
    Vector Center() const;
    void Center(const Vector& point);
    Rectangle Mirror_x(const Vector& point) const;
    Rectangle Mirror_y(const Vector& point) const;
    // return the point on the rectangle edge if arg is outside rectangle
    // return arg itself if arg is inside rectangle
    Vector Closest_point_to(const Vector& point) const;
private:
    Vector size;
};

class Circle
{
public:
    Vector center;
    Circle(const Vector& center, float r);
    void Draw(const ALLEGRO_COLOR& color) const;
    void Draw(const ALLEGRO_COLOR& line_color, float line_width) const;
    void Translate(const Vector& displacement);
    void Scale(float multiplier);
    void Add_radius_by(float value);
    bool Contain(const Vector& point) const;
    float Radius() const;
    Circle Mirror_x(const Vector& point) const;
    Circle Mirror_y(const Vector& point) const;
private:
    float radius;
};

class Triangle
{
public:
    Vector vertex_1;
    Vector vertex_2;
    Vector vertex_3;
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3);
    void Draw(const ALLEGRO_COLOR& color) const;
    void Draw(const ALLEGRO_COLOR& line_color, float line_width) const;
};
