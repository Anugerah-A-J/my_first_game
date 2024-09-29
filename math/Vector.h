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
    Vector& operator*=(float f);
    Vector& operator*=(const Matrix& m);
    Vector& operator/=(float f);
    Vector& operator+=(Vector v);
    Vector& operator-=(Vector v);
    Vector& operator-();
    Vector& unit();
private:
    float x;
    float y;
};

bool operator==(const Vector& v1, const Vector& v2);
bool operator!=(const Vector& v1, const Vector& v2);

bool operator>(const Vector& v1, const Vector& v2);
bool operator<=(const Vector& v1, const Vector& v2);

bool operator<(const Vector& v1, const Vector& v2);
bool operator>=(const Vector& v1, const Vector& v2);

Vector operator*(Vector v, float f);
Vector operator*(float f, Vector v);
Vector operator/(Vector v, float f);

Vector operator+(Vector v1, Vector v2);
Vector operator-(Vector v1, Vector v2);

float dot(const Vector& v1, const Vector& v2);

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4);
    const Vector& get_row(unsigned int ui) const;
private:
    std::array<Vector, 2> rows;
};

Vector operator*(const Matrix& m, Vector& v);