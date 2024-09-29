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

Vector& Vector::operator*=(float f)
{
    x *= f;
    y *= f;
    return *this;
}

Vector& Vector::operator*=(const Matrix &m)
{
    x = dot(m.get_row(1), *this);
    y = dot(m.get_row(2), *this);
    return *this;
}

Vector& Vector::operator/=(float f)
{
    x /= f;
    y /= f;
    return *this;
}

Vector& Vector::operator+=(Vector v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector& Vector::operator-=(Vector v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector& Vector::operator-()
{
    x = -x;
    y = -y;
    return *this;
}

Vector& Vector::unit()
{
    float mag = sqrtf(x * x + y * y);
    x /= mag;
    y /= mag;
    return *this;
}

bool operator==(const Vector& v1, const Vector& v2)
{
    return v1.get_x() == v2.get_x() && v1.get_y() == v2.get_y();
}

bool operator!=(const Vector& v1, const Vector& v2)
{
    return !(v1 == v2);
}

bool operator>(const Vector& v1, const Vector& v2)
{
    return v1.get_x() > v2.get_x() && v1.get_y() > v2.get_y();
}

bool operator<=(const Vector& v1, const Vector& v2)
{
    return !(v1 > v2);
}

bool operator<(const Vector& v1, const Vector& v2)
{
    return v1.get_x() < v2.get_x() && v1.get_y() < v2.get_y();
}

bool operator>=(const Vector& v1, const Vector& v2)
{
    return !(v1 < v2);
}

Vector operator*(Vector v, float f)
{
    return v *= f;
}
Vector operator*(float f, Vector v)
{
    return v *= f;
}
Vector operator/(Vector v, float f)
{
    return v /= f;
}

Vector operator+(Vector v1, Vector v2)
{
    return v1 += v2;
}

Vector operator-(Vector v1, Vector v2)
{
    return v1 -= v2;
}

float dot(const Vector& v1, const Vector& v2)
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

Vector operator*(const Matrix& m, Vector& v)
{
    return v *= m;
}