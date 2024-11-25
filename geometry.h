#include <math.h>
#include <allegro5/allegro_primitives.h>
#pragma once

bool Equal(float f1, float f2, float margin)
{
    return fabsf(f1 - f2) < margin;
}

bool Equal(const ALLEGRO_COLOR& color_1, const ALLEGRO_COLOR& color_2, float margin)
{
    return
        Equal(color_1.r, color_2.r, margin) &&
        Equal(color_1.g, color_2.g, margin) &&
        Equal(color_1.b, color_2.b, margin) &&
        Equal(color_1.a, color_2.a, margin);
}

class Vector
{
public:
    Vector(float x, float y): x{x}, y{y} {};
    
    float X() const { return x; };
    float Y() const { return y; };

    void X(float val) { x = val; };
    void Y(float val) { y = val; };

    Vector operator-() const { return Vector(-x, -y); };

    Vector operator+(const Vector& v) const { return Vector(x + v.x, y + v.y); };

    Vector operator-(const Vector& v) const { return Vector(x - v.x, y - v.y); };

    Vector operator*(float f) const { return Vector(x * f, y * f); };

    Vector operator/(float f) const { return Vector(x / f, y / f); };

    void operator*=(float f) { x *= f, y *= f; };

    void operator/=(float f) { x /= f, y /= f; };

    void operator+=(const Vector& v) { x += v.x, y += v.y; };

    void operator-=(const Vector& v) { x -= v.x, y -= v.y; };

    Vector Unit() const { return *this / sqrtf(x * x + y * y); };

    Vector Abs() const { return Vector(fabsf(x), fabsf(y)); };

    static float Dot(const Vector& v1, const Vector& v2);

    float Magsq() const { return x * x + y * y; };
private:
    float x;
    float y;
};

Vector operator*(float f, const Vector& v)
{
    return v * f;
};

float Vector::Dot(const Vector& v1, const Vector& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
};

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4): row_1{f1, f2}, row_2{f3, f4} {};
    const Vector& Row_1() const { return row_1; };
    const Vector& Row_2() const { return row_2; };
private:
    Vector row_1;
    Vector row_2;
};

Vector operator*(const Matrix& m, const Vector& v)
{
    return Vector(
        Vector::Dot(m.Row_1(), v),
        Vector::Dot(m.Row_2(), v)
    );
};

class Line
{
public:
    Line(float x1, float y1, float x2, float y2): start{x1, y1}, end{x2, y2} {};
    Line(float x, float y, const Vector& end): start{x, y}, end{end} {};
    Line(const Vector& start, float x, float y): start{start}, end{x, y} {};
    Line(const Vector& start, const Vector& end): start{start}, end{end} {};
    void Translate(const Vector& displacement) { start += displacement, end += displacement; };
    const Vector& Start() const { return start; }
    const Vector& End() const { return end; }
    void Draw() const
    {
        al_draw_line(
            start.X(),
            start.Y(),
            end.X(),
            end.Y(),
            al_map_rgb_f(0.5f, 0.5f, 0.5f),
            1
        );
    }
private:
    Vector start;
    Vector end;
};

class Rectangle
{
public:
    Rectangle(float x, float y, float w, float h, const ALLEGRO_COLOR& color, float line_width):
        origin{x, y},
        size{fabsf(w), fabsf(h)},
        color{color},
        line_width{line_width}
    {};

    Rectangle(const Vector& origin, const Vector& size, const ALLEGRO_COLOR& color, float line_width):
        origin{origin},
        size{size.Abs()},
        color{color},
        line_width{line_width}
    {};

    Rectangle(const Vector& origin, float height, const ALLEGRO_COLOR& color):
        origin{origin},
        size{0, height},
        color{color},
        line_width{0}
    {};

    void Draw() const
    {
        if (line_width == 0)
            al_draw_filled_rectangle(
                origin.X(),
                origin.Y(),
                origin.X() + size.X(),
                origin.Y() + size.Y(),
                color
            );
        else
            al_draw_rectangle(
                origin.X(),
                origin.Y(),
                origin.X() + size.X(),
                origin.Y() + size.Y(),
                color,
                line_width
            );
    }

    void Translate(const Vector& displacement) { origin += displacement; };

    Line Top() const { return Line(
        origin,
        origin.X() + size.X(),
        origin.Y()
    ); };

    Line Right() const { return Line(
        origin + size,
        origin.X() + size.X(),
        origin.Y()
    ); };

    Line Bottom() const { return Line(
        origin + size,
        origin.X(),
        origin.Y() + size.Y()
    ); }

    Line Left() const { return Line(
        origin,
        origin.X(),
        origin.Y() + size.Y()
    ); }

    bool Contain(const Vector& point) const
    {
        Vector distance_to_origin = point - origin;

        return 
            distance_to_origin.X() >= 0 &&
            distance_to_origin.Y() >= 0 &&
            distance_to_origin.X() <= size.X() &&
            distance_to_origin.Y() <= size.Y()
        ;
    }

    const Vector& Size() const { return size; }
    void Add_size_by(const Vector& value) { size += value; }
    
    float Width() const { return size.X(); }
    void Width(float val) { size.X(val); }

    float Height() const { return size.Y(); }
    void Height(float val) { size.Y(val); }
    
    const Vector& Origin() const { return origin; }
    void Origin(const Vector& origin) { this->origin = origin; }
private:
    Vector origin;
    Vector size;
    ALLEGRO_COLOR color;
    float line_width;
};

class Circle
{
public:
    Circle(float cx, float cy, float r, const ALLEGRO_COLOR& color, float line_width):
        center{cx, cy},
        radius{r},
        color{color},
        line_width{line_width}
    {};

    Circle(const Vector& center, float r, const ALLEGRO_COLOR& color, float line_width):
        center{center},
        radius{r},
        color{color},
        line_width{line_width}
    {};

    void Draw() const
    {
        if (line_width == 0)
            al_draw_filled_circle(
                center.X(),
                center.Y(),
                radius,
                color
            );
        else
            al_draw_circle(
                center.X(),
                center.Y(),
                radius,
                color,
                line_width
            );
    }

    void Translate(const Vector& displacement) { center += displacement; }
    void Translate(float x, float y) { center += Vector(x, y); }
    void Scale(float multiplier) { radius *= multiplier; }
    void Add_radius_by(float value) { radius += value; }

    void Transform_color_to(const ALLEGRO_COLOR& color, float color_transformation_ratio)
    {
        this->color.r += (color.r - this->color.r) * color_transformation_ratio;
        this->color.g += (color.g - this->color.g) * color_transformation_ratio;
        this->color.b += (color.b - this->color.b) * color_transformation_ratio;
        this->color.a += (color.a - this->color.a) * color_transformation_ratio;
    }

    bool Contain(const Vector& point) const
    {
        return (point - center).Magsq() <= radius * radius;
    }

    // void red(float red) { color_.r = red; }
    // void green(float green) { color_.g = green; }
    // void blue(float blue) { color_.b = blue; }
    // void alpha(float alpha) { color_.a = alpha; }

    const Vector& Center() const { return center; }
    void Center(const Vector& position) { center = position; }

    const ALLEGRO_COLOR& Color() const { return color; }
    void Color(const ALLEGRO_COLOR& color) { this->color = color; }

    float Radius() const { return radius; }

    void Line_width(float value) { line_width = value; }
    float Line_width() const { return line_width; }
private:
    Vector center;
    float radius;
    ALLEGRO_COLOR color;
    float line_width;
};

class Triangle
{
public:
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3, const ALLEGRO_COLOR& color, float line_width):
        vertex_1{vertex_1},
        vertex_2{vertex_2},
        vertex_3{vertex_3},
        color{color},
        line_width{line_width}
    {};

    void Draw() const
    {
        if (line_width == 0)
            al_draw_filled_triangle(
                vertex_1.X(),
                vertex_1.Y(),
                vertex_2.X(),
                vertex_2.Y(),
                vertex_3.X(),
                vertex_3.Y(),
                color
            );
        else
            al_draw_triangle(
                vertex_1.X(),
                vertex_1.Y(),
                vertex_2.X(),
                vertex_2.Y(),
                vertex_3.X(),
                vertex_3.Y(),
                color,
                line_width
            );
    }

    // void translate(const Vector& displacement)
    // {
    //     vertex_1_ += displacement;
    //     vertex_2_ += displacement;
    //     vertex_3_ += displacement;
    // }

    void Vertex_1(const Vector& point) { vertex_1 = point; }
    void Vertex_2(const Vector& point) { vertex_2 = point; }
    void Vertex_3(const Vector& point) { vertex_3 = point; }

    const Vector& Vertex_1() const { return vertex_1; }
    const Vector& Vertex_2() const { return vertex_2; }
    const Vector& Vertex_3() const { return vertex_3; }

    void Color(const ALLEGRO_COLOR& color) { this->color = color; }
private:
    Vector vertex_1;
    Vector vertex_2;
    Vector vertex_3;
    ALLEGRO_COLOR color;
    float line_width;
};