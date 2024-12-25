#include <allegro5/allegro_primitives.h>
#pragma once

bool Equal(float f1, float f2, float margin);

bool Equal(const ALLEGRO_COLOR& color_1, const ALLEGRO_COLOR& color_2, float margin);

void Transform_color(ALLEGRO_COLOR& changed_color, const ALLEGRO_COLOR& target_color, float color_transformation_ratio);

float Average(float f1, float f2);

class Vector
{
public:
    Vector(float x, float y);
    float X() const;
    float Y() const;
    void X(float val);
    void Y(float val);
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
    Vector Swap() const;
    Vector Unit() const;
    Vector Abs() const;
    static float Dot(const Vector& v1, const Vector& v2);
    float Magsq() const;
private:
    float x;
    float y;
};

Vector operator*(float f, const Vector& v);

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4);
    const Vector& Row_1() const;
    const Vector& Row_2() const;
private:
    Vector row_1;
    Vector row_2;
};

Vector operator*(const Matrix& m, const Vector& v);

class Line
{
public:
    Line(const Vector& start, const Vector& end);
    void Translate(const Vector& displacement);
    const Vector& Start() const;
    const Vector& End() const;
    float Length() const;
    void Draw(const ALLEGRO_COLOR& color, float line_width) const;
    Line Mirror_x(const Vector& point) const;
    Line Mirror_y(const Vector& point) const;
    Vector Direction() const;
    Vector Center() const;
    void Center(const Vector& point);
private:
    Vector start;
    Vector end;
};

class Rectangle
{
public:
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
    const Vector& Origin() const;
    void Origin(const Vector& origin);
    Vector Center() const;
    void Center(const Vector& point);
    Rectangle Mirror_x(const Vector& point) const;
    Rectangle Mirror_y(const Vector& point) const;
    // return the point on the rectangle edge if arg is outside rectangle
    // return arg itself if arg is inside rectangle
    Vector Closest_point_to(const Vector& point) const;
private:
    Vector origin;
    Vector size;
};

class Circle
{
public:
    Circle(const Vector& center, float r);
    void Draw(const ALLEGRO_COLOR& color) const;
    void Draw(const ALLEGRO_COLOR& line_color, float line_width) const;
    void Translate(const Vector& displacement);
    void Scale(float multiplier);
    void Add_radius_by(float value);
    bool Contain(const Vector& point) const;
    const Vector& Center() const;
    void Center(const Vector& position);
    float Radius() const;
    Circle Mirror_x(const Vector& point) const;
    Circle Mirror_y(const Vector& point) const;
private:
    Vector center;
    float radius;
};

class Triangle
{
public:
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3);
    void Draw(const ALLEGRO_COLOR& color) const;
    void Draw(const ALLEGRO_COLOR& line_color, float line_width) const;
    void Vertex_1(const Vector& point);
    void Vertex_2(const Vector& point);
    void Vertex_3(const Vector& point);
    const Vector& Vertex_1() const;
    const Vector& Vertex_2() const;
    const Vector& Vertex_3() const;
private:
    Vector vertex_1;
    Vector vertex_2;
    Vector vertex_3;
};

namespace Collision {
    float Circle_vs_circle(const Circle& moving_circle, const Circle& nonmoving_circle, const Line& velocity);
    float Circle_vs_line(const Circle& moving_circle, const Line& nonmoving_line, const Line& velocity);
    float Circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    float Circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    float Intersect(const Line& line1, const Line& line2);
    float Intersect(const Line& line, const Circle& circle);
};