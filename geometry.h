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
    Vector(float x, float y): x_{x}, y_{y} {};
    
    float x() const { return x_; };
    float y() const { return y_; };

    Vector operator-() const { return Vector(-x_, -y_); };

    Vector operator+(const Vector& v) const { return Vector(x_ + v.x_, y_ + v.y_); };

    Vector operator-(const Vector& v) const { return Vector(x_ - v.x_, y_ - v.y_); };

    Vector operator*(float f) const { return Vector(x_ * f, y_ * f); };

    Vector operator/(float f) const { return Vector(x_ / f, y_ / f); };

    void operator*=(float f) { x_ *= f, y_ *= f; };

    void operator/=(float f) { x_ /= f, y_ /= f; };

    void operator+=(const Vector& v) { x_ += v.x_, y_ += v.y_; };

    void operator-=(const Vector& v) { x_ -= v.x_, y_ -= v.y_; };

    Vector unit() const { return *this / sqrtf(x_ * x_ + y_ * y_); };

    Vector abs() const { return Vector(fabsf(x_), fabsf(y_)); };

    static float dot(const Vector& v1, const Vector& v2);

    float magsq() const { return x_ * x_ + y_ * y_; };
private:
    float x_;
    float y_;
};

Vector operator*(float f, const Vector& v)
{
    return v * f;
};

float Vector::dot(const Vector& v1, const Vector& v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
};

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4): row_1_{f1, f2}, row_2_{f3, f4} {};
    const Vector& row_1() const { return row_1_; };
    const Vector& row_2() const { return row_2_; };
private:
    Vector row_1_;
    Vector row_2_;
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
    Line(float x1, float y1, float x2, float y2): start_{x1, y1}, end_{x2, y2} {};
    Line(float x, float y, const Vector& end): start_{x, y}, end_{end} {};
    Line(const Vector& start, float x, float y): start_{start}, end_{x, y} {};
    Line(const Vector& start, const Vector& end): start_{start}, end_{end} {};
    void translate(const Vector& displacement) { start_ += displacement, end_ += displacement; };
    const Vector& start() const { return start_; }
    const Vector& end() const { return end_; }
private:
    Vector start_;
    Vector end_;
};

class Rectangle
{
public:
    Rectangle(float x, float y, float w, float h, const ALLEGRO_COLOR& color, float line_width):
        origin_{x, y},
        size_{fabsf(w), fabsf(h)},
        color_{color},
        line_width_{line_width}
    {};

    Rectangle(const Vector& origin, const Vector& size, const ALLEGRO_COLOR& color, float line_width):
        origin_{origin},
        size_{size.abs()},
        color_{color},
        line_width_{line_width}
    {};

    Rectangle(const ALLEGRO_COLOR& color):
        origin_{0, 0},
        size_{0, 0},
        color_{color},
        line_width_{0}
    {};

    void draw() const
    {
        if (line_width_ == 0)
            al_draw_filled_rectangle(
                origin_.x(),
                origin_.y(),
                origin_.x() + size_.x(),
                origin_.y() + size_.y(),
                color_
            );
        else
            al_draw_rectangle(
                origin_.x(),
                origin_.y(),
                origin_.x() + size_.x(),
                origin_.y() + size_.y(),
                color_,
                line_width_
            );
    }

    void translate(const Vector& displacement) { origin_ += displacement; };

    Line top() const { return Line(
        origin_,
        origin_.x() + size_.x(),
        origin_.y()
    ); };

    Line right() const { return Line(
        origin_ + size_,
        origin_.x() + size_.x(),
        origin_.y()
    ); };

    Line bottom() const { return Line(
        origin_ + size_,
        origin_.x(),
        origin_.y() + size_.y()
    ); }

    Line left() const { return Line(
        origin_,
        origin_.x(),
        origin_.y() + size_.y()
    ); }

    bool contain(const Vector& point) const
    {
        Vector distance_to_origin = point - origin_;

        return 
            distance_to_origin.x() >= 0 &&
            distance_to_origin.y() >= 0 &&
            distance_to_origin.x() <= size_.x() &&
            distance_to_origin.y() <= size_.y()
        ;
    }

    const Vector& size() const { return size_; }
    void add_size_by(const Vector& value) { size_ += value; }
private:
    Vector origin_;
    Vector size_;
    ALLEGRO_COLOR color_;
    float line_width_;
};

class Circle
{
public:
    Circle(float cx, float cy, float r, const ALLEGRO_COLOR& color, float line_width):
        center_{cx, cy},
        radius_{r},
        color_{color},
        line_width_{line_width}
    {};

    Circle(const Vector& center, float r, const ALLEGRO_COLOR& color, float line_width):
        center_{center},
        radius_{r},
        color_{color},
        line_width_{line_width}
    {};

    void draw() const
    {
        if (line_width_ == 0)
            al_draw_filled_circle(
                center_.x(),
                center_.y(),
                radius_,
                color_
            );
        else
            al_draw_circle(
                center_.x(),
                center_.y(),
                radius_,
                color_,
                line_width_
            );
    }

    void translate(const Vector& displacement) { center_ += displacement; }
    void translate(float x, float y) { center_ += Vector(x, y); }
    void scale(float multiplier) { radius_ *= multiplier; }
    void add_radius_by(float value) { radius_ += value; }

    void transform_color_to(const ALLEGRO_COLOR& color, float color_transformation_ratio)
    {
        color_.r += (color.r - color_.r) * color_transformation_ratio;
        color_.g += (color.g - color_.g) * color_transformation_ratio;
        color_.b += (color.b - color_.b) * color_transformation_ratio;
        color_.a += (color.a - color_.a) * color_transformation_ratio;
    }

    bool contain(const Vector& point) const
    {
        return (point - center_).magsq() <= radius_ * radius_;
    }

    // void red(float red) { color_.r = red; }
    // void green(float green) { color_.g = green; }
    // void blue(float blue) { color_.b = blue; }
    // void alpha(float alpha) { color_.a = alpha; }

    const Vector& center() const { return center_; }
    void center(const Vector& position) { center_ = position; }

    const ALLEGRO_COLOR& color() const { return color_; }
    void color(const ALLEGRO_COLOR& color) { color_ = color; }

    float radius() const { return radius_; }
private:
    Vector center_;
    float radius_;
    ALLEGRO_COLOR color_;
    float line_width_;
};

class Triangle
{
public:
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3, const ALLEGRO_COLOR& color, float line_width):
        vertex_1_{vertex_1},
        vertex_2_{vertex_2},
        vertex_3_{vertex_3},
        color_{color},
        line_width_{line_width}
    {};

    void draw() const
    {
        if (line_width_ == 0)
            al_draw_filled_triangle(
                vertex_1_.x(),
                vertex_1_.y(),
                vertex_2_.x(),
                vertex_2_.y(),
                vertex_3_.x(),
                vertex_3_.y(),
                color_
            );
        else
            al_draw_triangle(
                vertex_1_.x(),
                vertex_1_.y(),
                vertex_2_.x(),
                vertex_2_.y(),
                vertex_3_.x(),
                vertex_3_.y(),
                color_,
                line_width_
            );
    }

    // void translate(const Vector& displacement)
    // {
    //     vertex_1_ += displacement;
    //     vertex_2_ += displacement;
    //     vertex_3_ += displacement;
    // }

    void vertex_1(const Vector& point) { vertex_1_ = point; }
    void vertex_2(const Vector& point) { vertex_2_ = point; }
    void vertex_3(const Vector& point) { vertex_3_ = point; }

    const Vector& vertex_1() const { return vertex_1_; }
    const Vector& vertex_2() const { return vertex_2_; }
    const Vector& vertex_3() const { return vertex_3_; }

    void color(const ALLEGRO_COLOR& color) { color_ = color; }
private:
    Vector vertex_1_;
    Vector vertex_2_;
    Vector vertex_3_;
    ALLEGRO_COLOR color_;
    float line_width_;
};