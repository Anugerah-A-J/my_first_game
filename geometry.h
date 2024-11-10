#include <math.h>
#pragma once

bool equal(float f1, float f2, float margin)
{
    return fabsf(f1 - f2) < margin;
}

bool equal(const ALLEGRO_COLOR& color_1, const ALLEGRO_COLOR& color_2, float margin)
{
    return
        equal(color_1.r, color_2.r, margin) &&
        equal(color_1.g, color_2.g, margin) &&
        equal(color_1.b, color_2.b, margin) &&
        equal(color_1.a, color_2.a, margin);
}

class Vector
{
public:
    Vector(float x, float y): X{x}, Y{y} {};
    
    float x() const { return X; };
    float y() const { return Y; };

    Vector operator-() const { return Vector(-X, -Y); };

    Vector operator+(const Vector& v) const { return Vector(X + v.X, Y + v.Y); };

    Vector operator-(const Vector& v) const { return Vector(X - v.X, Y - v.Y); };

    Vector operator*(float f) const { return Vector(X * f, Y * f); };

    Vector operator/(float f) const { return Vector(X / f, Y / f); };

    void operator*=(float f) { X *= f, Y *= f; };

    void operator/=(float f) { X /= f, Y /= f; };

    void operator+=(const Vector& v) { X += v.X, Y += v.Y; };

    void operator-=(const Vector& v) { X -= v.X, Y -= v.Y; };

    Vector unit() const { return *this / sqrtf(X * X + Y * Y); };

    Vector abs() const { return Vector(fabsf(X), fabsf(Y)); };

    static float dot(const Vector& v1, const Vector& v2);

    float magsq() const { return X * X + Y * Y; };
private:
    float X;
    float Y;
};

Vector operator*(float f, const Vector& v)
{
    return v * f;
};

float Vector::dot(const Vector& v1, const Vector& v2)
{
    return v1.X * v2.X + v1.Y * v2.Y;
};

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4): Row_1{f1, f2}, Row_2{f3, f4} {};
    const Vector& row_1() const { return Row_1; };
    const Vector& row_2() const { return Row_2; };
private:
    Vector Row_1;
    Vector Row_2;
};

Vector operator*(const Matrix& m, const Vector& v)
{
    return Vector(
        Vector::dot(m.row_1(), v),
        Vector::dot(m.row_2(), v)
    );
};

class Line
{
public:
    Line(float x1, float y1, float x2, float y2): Start{x1, y1}, End{x2, y2} {};
    Line(float x, float y, const Vector& end): Start{x, y}, End{end} {};
    Line(const Vector& start, float x, float y): Start{start}, End{x, y} {};
    Line(const Vector& start, const Vector& end): Start{start}, End{end} {};
    void translate(const Vector& displacement) { Start += displacement, End += displacement; };
    const Vector& start() const { return Start; }
    const Vector& end() const { return End; }
private:
    Vector Start;
    Vector End;
};

class Rectangle
{
public:
    Rectangle(float x, float y, float w, float h, const ALLEGRO_COLOR& color, float line_width):
        Origin{x, y},
        Size{fabsf(w), fabsf(h)},
        Color{color},
        Line_width{line_width}
    {};

    Rectangle(const Vector& origin, const Vector& size, const ALLEGRO_COLOR& color, float line_width):
        Origin{origin},
        Size{size.abs()},
        Color{color},
        Line_width{line_width}
    {};

    void draw() const
    {
        if (Line_width == 0)
            al_draw_filled_rectangle(
                Origin.x(),
                Origin.y(),
                Origin.x() + Size.x(),
                Origin.y() + Size.y(),
                Color
            );
        else
            al_draw_rectangle(
                Origin.x(),
                Origin.y(),
                Origin.x() + Size.x(),
                Origin.y() + Size.y(),
                Color,
                Line_width
            );
    }

    void translate(const Vector& displacement) { Origin += displacement; };

    Line top() const { return Line(
        Origin,
        Origin.x() + Size.x(),
        Origin.y()
    ); };

    Line right() const { return Line(
        Origin + Size,
        Origin.x() + Size.x(),
        Origin.y()
    ); };

    Line bottom() const { return Line(
        Origin + Size,
        Origin.x(),
        Origin.y() + Size.y()
    ); }

    Line left() const { return Line(
        Origin,
        Origin.x(),
        Origin.y() + Size.y()
    ); }

    const Vector& size() const { return Size; }
    void add_size_by(const Vector& value) { Size += value; }
private:
    Vector Origin;
    Vector Size;
    ALLEGRO_COLOR Color;
    float Line_width;
};

class Circle
{
public:
    Circle(float cx, float cy, float r, const ALLEGRO_COLOR& color, float line_width):
        Center{cx, cy},
        Radius{r},
        Color{color},
        Line_width{line_width}
    {};

    Circle(const Vector& center, float r, const ALLEGRO_COLOR& color, float line_width):
        Center{center},
        Radius{r},
        Color{color},
        Line_width{line_width}
    {};

    void draw() const
    {
        if (Line_width == 0)
            al_draw_filled_circle(
                Center.x(),
                Center.y(),
                Radius,
                Color
            );
        else
            al_draw_circle(
                Center.x(),
                Center.y(),
                Radius,
                Color,
                Line_width
            );
    }

    void translate(const Vector& displacement) { Center += displacement; }
    void translate(float x, float y) { Center += Vector(x, y); }
    void scale(float multiplier) { Radius *= multiplier; }
    void add_radius_by(float value) { Radius += value; }

    void transform_color_to(const ALLEGRO_COLOR& color, float color_transformation_ratio)
    {
        Color.r += (color.r - Color.r) * color_transformation_ratio;
        Color.g += (color.g - Color.g) * color_transformation_ratio;
        Color.b += (color.b - Color.b) * color_transformation_ratio;
        Color.a += (color.a - Color.a) * color_transformation_ratio;
    }

    // void red(float red) { Color.r = red; }
    // void green(float green) { Color.g = green; }
    // void blue(float blue) { Color.b = blue; }
    // void alpha(float alpha) { Color.a = alpha; }

    const Vector& center() const { return Center; }
    void center(const Vector& position) { Center = position; }

    const ALLEGRO_COLOR& color() const { return Color; }
    void color(const ALLEGRO_COLOR& color) { Color = color; }

    float radius() const { return Radius; }
private:
    Vector Center;
    float Radius;
    ALLEGRO_COLOR Color;
    float Line_width;
};

class Triangle
{
public:
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3, const ALLEGRO_COLOR& color, float line_width):
        Vertex_1{vertex_1},
        Vertex_2{vertex_2},
        Vertex_3{vertex_3},
        Color{color},
        Line_width{line_width}
    {};

    void draw() const
    {
        if (Line_width == 0)
            al_draw_filled_triangle(
                Vertex_1.x(),
                Vertex_1.y(),
                Vertex_2.x(),
                Vertex_2.y(),
                Vertex_3.x(),
                Vertex_3.y(),
                Color
            );
        else
            al_draw_triangle(
                Vertex_1.x(),
                Vertex_1.y(),
                Vertex_2.x(),
                Vertex_2.y(),
                Vertex_3.x(),
                Vertex_3.y(),
                Color,
                Line_width
            );
    }

    // void translate(const Vector& displacement)
    // {
    //     Vertex_1 += displacement;
    //     Vertex_2 += displacement;
    //     Vertex_3 += displacement;
    // }

    void vertex_1(const Vector& point) { Vertex_1 = point; }
    void vertex_2(const Vector& point) { Vertex_2 = point; }
    void vertex_3(const Vector& point) { Vertex_3 = point; }

    const Vector& vertex_1() const { return Vertex_1; }
    const Vector& vertex_2() const { return Vertex_2; }
    const Vector& vertex_3() const { return Vertex_3; }

    void color(const ALLEGRO_COLOR& color) { Color = color; }
private:
    Vector Vertex_1;
    Vector Vertex_2;
    Vector Vertex_3;
    ALLEGRO_COLOR Color;
    float Line_width;
};