#include <math.h>
#pragma once

bool equal(float f1, float f2, float margin)
{
    return fabsf(f1 - f2) < margin;
}

struct Vector
{
    float x;
    float y;
    float magsq;

    Vector(float x, float y)
    :
        x{x}, y{y}, magsq{x * x + y * y}
    {};

    Vector operator-() const
    {
        return Vector(-x, -y);
    };

    Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y);
    };

    Vector operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y);
    };

    Vector operator*(float f) const
    {
        return Vector(x * f, y * f);
    };

    Vector operator/(float f) const
    {
        return Vector(x / f, y / f);
    };

    void operator*=(float f)
    {
        x *= f, y *= f;
    };

    void operator/=(float f)
    {
        x /= f, y /= f;
    };

    void operator+=(const Vector& v)
    {
        x += v.x, y += v.y;
    };

    void operator-=(const Vector& v)
    {
        x -= v.x, y -= v.y;
    };

    Vector unit()
    {
        return *this / sqrtf(magsq);
    };
};

Vector operator*(float f, const Vector& v)
{
    return v * f;
};

float dot(const Vector& v1, const Vector& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
};

struct Matrix
{
    Vector row_1;
    Vector row_2;

    Matrix(float f1, float f2, float f3, float f4)
    :
        row_1{f1, f2},
        row_2{f3, f4}
    {};
};

Vector operator*(const Matrix& m, const Vector& v)
{
    return Vector(
        dot(m.row_1, v),
        dot(m.row_2, v)
    );
};

struct Line
{
    Vector start;
    Vector end;

    Line(const Vector& start, const Vector& end)
    :
        start{start}, end{end}
    {};

    void translate(const Vector& displacement)
    {
        start += displacement;
        end += displacement;
    };
};

struct Rectangle
{
    Vector start;
    Vector size;
    Vector end;
    
    Rectangle(float x, float y, float w, float h)
    :
        start{x, y},
        size{fabsf(w), fabsf(h)},
        end{start + Vector(w, h)}
    {};

    void translate(const Vector& displacement)
    {
        start += displacement;
        end += displacement;
    };

    Line top() const
    {
        Vector size = end - start;
        return Line(start, start + Vector(size.x, 0));
    };

    Line right() const
    {
        Vector size = end - start;
        return Line(end, end - Vector(0, size.y));
    };

    Line bottom() const
    {
        Vector size = end - start;
        return Line(end, end - Vector(size.x, 0));
    };

    Line left() const
    {
        Vector size = end - start;
        return Line(start, start + Vector(0, size.y));
    }
};

struct Circle
{
    Vector center;
    float radius;

    Circle(float cx, float cy, float r)
    :
        center{cx, cy}, radius{r}
    {};
    // Circle(const Circle& circle, const Vector& vector):
    //     center{circle.center + vector},
    //     radius{circle.radius}
    // {};
};

struct Triangle
{
    Vector vertex_1;
    Vector vertex_2;
    Vector vertex_3;

    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3)
    :
        vertex_1{vertex_1}, vertex_2{vertex_2}, vertex_3{vertex_3}
    {};

    void translate(const Vector& displacement)
    {
        vertex_1 += displacement;
        vertex_2 += displacement;
        vertex_3 += displacement;
    };
};