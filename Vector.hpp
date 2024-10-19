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