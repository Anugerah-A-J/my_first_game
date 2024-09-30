#include <array>
#pragma once

class Matrix;

class Vector
{
public:
    explicit Vector(float f);
    Vector(float x, float y);
    float get_x() const;
    float get_y() const;
    float magsq() const;
    Vector operator-() const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(float f) const;
    Vector operator/(float f) const;

    void operator*=(float f);
    void operator*=(const Matrix& m);
    void operator/=(float f);
    void operator+=(Vector v);
    void operator-=(Vector v);
    void unit();

    bool operator==(const Vector& v);
    bool operator!=(const Vector& v);
    bool operator>(const Vector& v);
    bool operator<=(const Vector& v);
    bool operator<(const Vector& v);
    bool operator>=(const Vector& v);
private:
    float x;
    float y;
};

Vector operator*(float f, const Vector& v);
float dot(const Vector& v1, const Vector& v2);

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4);
    const Vector& get_row(unsigned int ui) const;
private:
    std::array<Vector, 2> rows;
};

Vector operator*(const Matrix& m, const Vector& v);