#include "Shape.hpp"
#include <algorithm>
#include <math.h>

void Println()
{
    std::cout << '\n';
}

bool Equal(float f1, float f2, float margin)
{
    return fabsf(f1 - f2) < margin;
}

bool Equal(const ALLEGRO_COLOR& color_1, const ALLEGRO_COLOR& color_2, float margin)
{
    return Equal(color_1.r, color_2.r, margin) && Equal(color_1.g, color_2.g, margin)
        && Equal(color_1.b, color_2.b, margin) && Equal(color_1.a, color_2.a, margin);
}

void Transform_color(ALLEGRO_COLOR& changed_color, const ALLEGRO_COLOR& target_color, float color_transformation_ratio)
{
    changed_color.r += (target_color.r - changed_color.r) * color_transformation_ratio;
    changed_color.g += (target_color.g - changed_color.g) * color_transformation_ratio;
    changed_color.b += (target_color.b - changed_color.b) * color_transformation_ratio;
    changed_color.a += (target_color.a - changed_color.a) * color_transformation_ratio;
}

float Average(float f1, float f2)
{
    return (f1 + f2) / 2;
}

float Square(float f)
{
    return f * f;
}

Vector operator*(float f, const Vector& v)
{
    return v * f;
}

Vector operator*(const Matrix& m, const Vector& v)
{
    return Vector(Vector::Dot(m.row_1, v), Vector::Dot(m.row_2, v));
}

Vector::Vector(float x, float y)
:
    x{x},
    y{y}
{}

Vector Vector::operator-() const
{
    return Vector(-x, -y);
}

Vector Vector::operator+(const Vector& v) const
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector& v) const
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

void Vector::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
}

void Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
}

bool Vector::operator==(const Vector& v) const
{
    return v.x == x && v.y == y;
}

bool Vector::operator!=(const Vector& v) const
{
    return !(*this == v);
}

Vector Vector::Swap() const
{
    return Vector(y, x);
}

Vector Vector::Unit() const
{
    return *this / sqrtf(x * x + y * y);
}

Vector Vector::Abs() const
{
    return Vector(fabsf(x), fabsf(y));
}

float Vector::Dot(const Vector& v1, const Vector& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float Vector::Magsq() const
{
    return x * x + y * y;
}

Matrix::Matrix(float f1, float f2, float f3, float f4)
:
    row_1{f1, f2},
    row_2{f3, f4}
{}

Line::Line(const Vector& start, const Vector& end)
:
    start{start},
    end{end}
{}

void Line::Translate(const Vector& displacement)
{
    start += displacement;
    end += displacement;
}

float Line::Length() const
{
    return std::sqrtf((start - end).Magsq());
}

void Line::Draw(const ALLEGRO_COLOR& color, float line_width) const
{
    al_draw_line(start.x, start.y, end.x, end.y, color, line_width);
}

Line Line::Mirror_x(const Vector& point) const
{
    Vector translate_start = Vector(0, (point - start).y) * 2;
    Vector translate_end = Vector(0, (point - end).y) * 2;

    return Line(start + translate_start, end + translate_end);
}

Line Line::Mirror_y(const Vector& point) const
{
    Vector translate_start = Vector((point - start).x, 0) * 2;
    Vector translate_end = Vector((point - end).x, 0) * 2;

    return Line(start + translate_start, end + translate_end);
}

Vector Line::Center() const
{
    return Vector(
        Average(start.x, end.x),
        Average(start.y, end.y)
    );
}

void Line::Center(const Vector& point)
{
    Translate(point - Center());
}

Vector Line::Direction() const
{
    return end - start;
}

    
Rectangle::Rectangle(const Vector& origin, const Vector& size)
:
    origin{origin},
    size{size.Abs()}
{}

void Rectangle::Draw(const ALLEGRO_COLOR& color) const
{
    al_draw_filled_rectangle(origin.x, origin.y, origin.x + size.x, origin.y + size.y, color);
}

void Rectangle::Draw(const ALLEGRO_COLOR& line_color, float line_width) const
{
    al_draw_rectangle(origin.x, origin.y, origin.x + size.x, origin.y + size.y, line_color, line_width);
}

void Rectangle::Translate(const Vector& displacement)
{
    origin += displacement;
}

Vector Rectangle::Top_left() const
{
    return origin;
}

Vector Rectangle::Top_right() const
{
    return origin + Vector(size.x, 0);
}

Vector Rectangle::Bottom_right() const
{
    return origin + size;
}

Vector Rectangle::Bottom_left() const
{
    return origin + Vector(0, size.y);
}

Line Rectangle::Top() const
{
    return Line(Top_left(), Top_right());
}

Line Rectangle::Right() const
{
    return Line(Top_right(), Bottom_right());
}

Line Rectangle::Bottom() const
{
    return Line(Bottom_left(), Bottom_right());
}

Line Rectangle::Left() const
{
    return Line(Top_left(), Bottom_left());
}

bool Rectangle::Contain(const Vector& point) const
{
    Vector distance_to_origin = point - origin;

    return distance_to_origin.x >= 0 && distance_to_origin.y >= 0
        && distance_to_origin.x <= size.x && distance_to_origin.y <= size.y;
}

const Vector& Rectangle::Size() const
{
    return size;
}

void Rectangle::Add_size_by(const Vector& value)
{
    size += value;

    if (size.x < 0)
        size.x = 0;

    if (size.y < 0)
        size.y = 0;
}

float Rectangle::Width() const
{
    return size.x;
}

void Rectangle::Width(float val)
{
    size.x = fabsf(val);
}

float Rectangle::Height() const
{
    return size.y;
}

void Rectangle::Height(float val)
{
    size.y = fabsf(val);
}

Vector Rectangle::Center() const
{
    return origin + size / 2;
}

void Rectangle::Center(const Vector& point)
{
    Translate(point - Center());
}

Rectangle Rectangle::Mirror_x(const Vector& point) const
{
    Vector center = Center();
    Vector translate = Vector(0, (point - center).y);

    return Rectangle(center + translate * 2 - size / 2, size);
}

Rectangle Rectangle::Mirror_y(const Vector& point) const
{
    Vector center = Center();
    Vector translate = Vector((point - center).x, 0);

    return Rectangle(center + translate * 2 - size / 2, size);
}

// return the point on the rectangle edge if arg is outside rectangle
// return arg itself if arg is inside rectangle
Vector Rectangle::Closest_point_to(const Vector& point) const
{
    float x = point.x;
    x = std::max(x, origin.x);
    x = std::min(x, (origin + size).x);

    float y = point.y;
    y = std::max(y, origin.y);
    y = std::min(y, (origin + size).y);

    return Vector(x, y);
}
    
Circle::Circle(const Vector& center, float r)
:
    center{center},
    radius{fabsf(r)}
{}

void Circle::Draw(const ALLEGRO_COLOR& color) const
{
    al_draw_filled_circle(center.x, center.y, radius, color);
}

void Circle::Draw(const ALLEGRO_COLOR& line_color, float line_width) const
{
    al_draw_circle(center.x, center.y, radius, line_color, line_width);
}

void Circle::Translate(const Vector& displacement)
{
    center += displacement;
}

void Circle::Scale(float multiplier)
{
    radius *= fabsf(multiplier);
}

void Circle::Add_radius_by(float value)
{
    radius += value;

    if (radius < 0)
        radius = 0;
}

bool Circle::Contain(const Vector& point) const
{
    return (point - center).Magsq() <= radius * radius;
}

float Circle::Radius() const
{
    return radius;
}

Circle Circle::Mirror_x(const Vector& point) const
{
    Vector translate = Vector(0, (point - center).y);

    return Circle(center + translate * 2, radius);
}

Circle Circle::Mirror_y(const Vector& point) const
{
    Vector translate = Vector((point - center).x, 0);

    return Circle(center + translate * 2, radius);
}
    
Triangle::Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3)
:
    vertex_1{vertex_1},
    vertex_2{vertex_2},
    vertex_3{vertex_3}
{}

void Triangle::Draw(const ALLEGRO_COLOR& color) const
{
    al_draw_filled_triangle(
        vertex_1.x,
        vertex_1.y,
        vertex_2.x,
        vertex_2.y,
        vertex_3.x,
        vertex_3.y,
        color
    );
}

void Triangle::Draw(const ALLEGRO_COLOR& line_color, float line_width) const
{
    al_draw_triangle(
        vertex_1.x,
        vertex_1.y,
        vertex_2.x,
        vertex_2.y,
        vertex_3.x,
        vertex_3.y,
        line_color,
        line_width
    );
}
