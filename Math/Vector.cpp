#include "Vector.h"
#include <cmath>

Vector::Vector(float f)
:
    x{f}, y{f}
{}

Vector::Vector(float x, float y)
:
    x{x}, y{y}
{}

float Vector::get_x() const
{
    return x;
}

float Vector::get_y() const
{
    return y;
}

float Vector::magsq() const
{
    return x * x + y * y;
}

Vector Vector::operator-() const
{
    return Vector(-x, -y);
}

Vector Vector::operator+(const Vector &v) const
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector &v) const
{
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator*(float f) const
{
    return Vector(x * f, y * f);
}

Vector Vector::operator/(float f) const
{
    return Vector(x / f, y / f);
}

void Vector::operator*=(float f)
{
    x *= f;
    y *= f;
}

void Vector::operator/=(float f)
{
    x /= f;
    y /= f;
}

void Vector::operator+=(Vector v)
{
    x += v.x;
    y += v.y;
}

void Vector::operator-=(Vector v)
{
    x -= v.x;
    y -= v.y;
}

void Vector::unit()
{
    float mag = sqrtf(x * x + y * y);
    x /= mag;
    y /= mag;
}

bool Vector::operator==(const Vector &v)
{
    return x == v.x && y == v.y;
}

bool Vector::operator!=(const Vector &v)
{
    return x != v.x || y != v.y;
}

bool Vector::operator>(const Vector &v)
{
    return x > v.x && y > v.y;
}

bool Vector::operator<=(const Vector &v)
{
    return x <= v.x && y <= v.y;
}

bool Vector::operator<(const Vector &v)
{
    return x < v.x && y < v.y;
}

bool Vector::operator>=(const Vector &v)
{
    return x >= v.x && y >= v.y;
}

Vector operator*(float f, const Vector &v)
{
    return v * f;
}

float dot(const Vector &v1, const Vector &v2)
{
    return v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y();
}

Matrix::Matrix(float f1, float f2, float f3, float f4)
:
    rows{Vector(f1, f2), Vector(f3, f4)}
{}

const Vector& Matrix::get_row(unsigned int ui) const
{
    return rows.at(ui - 1);
}

Vector operator*(const Matrix& m, const Vector& v)
{
    return Vector(
        dot(m.get_row(1), v),
        dot(m.get_row(2), v)
    );
}