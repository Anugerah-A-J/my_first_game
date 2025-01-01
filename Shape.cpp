#include "Shape.hpp"
#include "Param.hpp"
#include <algorithm>
#include <set>
#include <math.h>

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
    return Vector(Vector::Dot(m.Row_1(), v), Vector::Dot(m.Row_2(), v));
}

Vector::Vector(float x, float y)
:
    x{x},
    y{y}
{}

float Vector::X() const
{
    return x;
}

float Vector::Y() const
{
    return y;
}

void Vector::X(float val)
{
    x = val;
}

void Vector::Y(float val)
{
    y = val;
}

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

const Vector& Matrix::Row_1() const
{
    return row_1;
}

const Vector& Matrix::Row_2() const
{
    return row_2;
}

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

const Vector& Line::Start() const
{
    return start;
}

const Vector& Line::End() const
{
    return end;
}

float Line::Length() const
{
    return std::sqrtf((start - end).Magsq());
}

void Line::Draw(const ALLEGRO_COLOR& color, float line_width) const
{
    al_draw_line(start.X(), start.Y(), end.X(), end.Y(), color, line_width);
}

Line Line::Mirror_x(const Vector& point) const
{
    Vector translate_start = Vector(0, (point - start).Y()) * 2;
    Vector translate_end = Vector(0, (point - end).Y()) * 2;

    return Line(start + translate_start, end + translate_end);
}

Line Line::Mirror_y(const Vector& point) const
{
    Vector translate_start = Vector((point - start).X(), 0) * 2;
    Vector translate_end = Vector((point - end).X(), 0) * 2;

    return Line(start + translate_start, end + translate_end);
}

Vector Line::Center() const
{
    return Vector(
        Average(start.X(), end.X()),
        Average(start.Y(), end.Y())
    );
}

void Line::Center(const Vector& point)
{
    Translate(point - Center());
}
    
Rectangle::Rectangle(const Vector& origin, const Vector& size)
:
    origin{origin},
    size{size.Abs()}
{}

void Rectangle::Draw(const ALLEGRO_COLOR& color) const
{
    al_draw_filled_rectangle(origin.X(), origin.Y(), origin.X() + size.X(), origin.Y() + size.Y(), color);
}

void Rectangle::Draw(const ALLEGRO_COLOR& line_color, float line_width) const
{
    al_draw_rectangle(origin.X(), origin.Y(), origin.X() + size.X(), origin.Y() + size.Y(), line_color, line_width);
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
    return origin + Vector(size.X(), 0);
}

Vector Rectangle::Bottom_right() const
{
    return origin + size;
}

Vector Rectangle::Bottom_left() const
{
    return origin + Vector(0, size.Y());
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

    return distance_to_origin.X() >= 0 && distance_to_origin.Y() >= 0
        && distance_to_origin.X() <= size.X() && distance_to_origin.Y() <= size.Y();
}

const Vector& Rectangle::Size() const
{
    return size;
}

void Rectangle::Add_size_by(const Vector& value)
{
    size += value;
}

float Rectangle::Width() const
{
    return size.X();
}

void Rectangle::Width(float val)
{
    size.X(val);
}

float Rectangle::Height() const
{
    return size.Y();
}

void Rectangle::Height(float val)
{
    size.Y(val);
}

const Vector& Rectangle::Origin() const
{
    return origin;
}

void Rectangle::Origin(const Vector& origin)
{
    this->origin = origin;
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
    Vector translate = Vector(0, (point - center).Y());

    return Rectangle(center + translate * 2 - size / 2, size);
}

Rectangle Rectangle::Mirror_y(const Vector& point) const
{
    Vector center = Center();
    Vector translate = Vector((point - center).X(), 0);

    return Rectangle(center + translate * 2 - size / 2, size);
}

// return the point on the rectangle edge if arg is outside rectangle
// return arg itself if arg is inside rectangle
Vector Rectangle::Closest_point_to(const Vector& point) const
{
    float x = point.X();
    x = std::max(x, origin.X());
    x = std::min(x, (origin + size).X());

    float y = point.Y();
    y = std::max(y, origin.Y());
    y = std::min(y, (origin + size).Y());

    return Vector(x, y);
}
    
Circle::Circle(const Vector& center, float r)
:
    center{center},
    radius{r}
{}

void Circle::Draw(const ALLEGRO_COLOR& color) const
{
    al_draw_filled_circle(center.X(), center.Y(), radius, color);
}

void Circle::Draw(const ALLEGRO_COLOR& line_color, float line_width) const
{
    al_draw_circle(center.X(), center.Y(), radius, line_color, line_width);
}

void Circle::Translate(const Vector& displacement)
{
    center += displacement;
}

void Circle::Scale(float multiplier)
{
    radius *= multiplier;
}

void Circle::Add_radius_by(float value)
{
    radius += value;
}

bool Circle::Contain(const Vector& point) const
{
    return (point - center).Magsq() <= radius * radius;
}

const Vector& Circle::Center() const
{
    return center;
}
void Circle::Center(const Vector& position)
{
    center = position;
}

float Circle::Radius() const
{
    return radius;
}

Circle Circle::Mirror_x(const Vector& point) const
{
    Vector translate = Vector(0, (point - center).Y());

    return Circle(center + translate * 2, radius);
}

Circle Circle::Mirror_y(const Vector& point) const
{
    Vector translate = Vector((point - center).X(), 0);

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
        vertex_1.X(),
        vertex_1.Y(),
        vertex_2.X(),
        vertex_2.Y(),
        vertex_3.X(),
        vertex_3.Y(),
        color
    );
}

void Triangle::Draw(const ALLEGRO_COLOR& line_color, float line_width) const
{
    al_draw_triangle(
        vertex_1.X(),
        vertex_1.Y(),
        vertex_2.X(),
        vertex_2.Y(),
        vertex_3.X(),
        vertex_3.Y(),
        line_color,
        line_width
    );
}

void Triangle::Vertex_1(const Vector& point)
{
    vertex_1 = point;
}

void Triangle::Vertex_2(const Vector& point)
{
    vertex_2 = point;
}

void Triangle::Vertex_3(const Vector& point)
{
    vertex_3 = point;
}

const Vector& Triangle::Vertex_1() const
{
    return vertex_1;
}

const Vector& Triangle::Vertex_2() const
{
    return vertex_2;
}

const Vector& Triangle::Vertex_3() const
{
    return vertex_3;
}

// float Collision::Circle_vs_line(const Circle& moving_circle, const Line& nonmoving_line, const Line& velocity)
// {
//     Line line_1 = nonmoving_line;
//     Line line_2 = nonmoving_line;
//     Circle start = moving_circle;
//     Circle end = moving_circle;

//     Vector translate = nonmoving_line.Direction().Unit().Swap() * moving_circle.Radius();

//     line_1.Translate(translate);
//     line_2.Translate(-translate);
//     start.Center(nonmoving_line.Start());
//     end.Center(nonmoving_line.End());

//     std::vector<float> ts;
//     ts.reserve(4);

//     ts.push_back(Intersect(velocity, line_1));
//     ts.push_back(Intersect(velocity, line_2));
//     ts.push_back(Intersect(velocity, start));
//     ts.push_back(Intersect(velocity, end));

//     return *std::min_element(ts.begin(), ts.end());
// }

// float Collision::Circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity)
// {
//     // Vector rectangle_to_circle_past = velocity.Start()
//     //                                   - nonmoving_rectangle.Closest_point_to(velocity.Start());

//     // if (rectangle_to_circle_past.Magsq() <= moving_circle.Radius() * moving_circle.Radius()) {
//     //     if (Vector::Dot(rectangle_to_circle_past, velocity.Direction()) >= 0)
//     //         return 2; // angle <= abs(90)
//     //     // if () return 0; // angle > abs(90)
//     // }

//     Line top = nonmoving_rectangle.Top();
//     Line right = nonmoving_rectangle.Right();
//     Line bottom = nonmoving_rectangle.Bottom();
//     Line left = nonmoving_rectangle.Left();

//     Circle top_left = moving_circle;
//     Circle top_right = moving_circle;
//     Circle bottom_right = moving_circle;
//     Circle bottom_left = moving_circle;

//     top_left.Center(nonmoving_rectangle.Top_left());
//     top_right.Center(nonmoving_rectangle.Top_right());
//     bottom_right.Center(nonmoving_rectangle.Bottom_right());
//     bottom_left.Center(nonmoving_rectangle.Bottom_left());

//     top.Translate(Vector(0, -moving_circle.Radius()));
//     right.Translate(Vector(moving_circle.Radius(), 0));
//     bottom.Translate(Vector(0, moving_circle.Radius()));
//     left.Translate(Vector(-moving_circle.Radius(), 0));

//     std::vector<float> ts;
//     ts.reserve(8);

//     ts.push_back(Intersect(velocity, top));
//     ts.push_back(Intersect(velocity, right));
//     ts.push_back(Intersect(velocity, bottom));
//     ts.push_back(Intersect(velocity, left));

//     ts.push_back(Intersect(velocity, top_left));
//     ts.push_back(Intersect(velocity, top_right));
//     ts.push_back(Intersect(velocity, bottom_right));
//     ts.push_back(Intersect(velocity, bottom_left));

//     return *std::min_element(ts.begin(), ts.end());
// }

void Collision::Reflect_circle_inside_rectangle(Circle &moving_circle, Translation &circle_translation, const Rectangle &nonmoving_rectangle)
{
    Rectangle rectangle = nonmoving_rectangle;
    rectangle.Translate(Vector(moving_circle.Radius(), moving_circle.Radius()));
    rectangle.Add_size_by(-2 * Vector(moving_circle.Radius(), moving_circle.Radius()));

    // std::vector<float> ts = {
    //     Intersect(circle_translation.Latest_translation(), rectangle.Top()),
    //     Intersect(circle_translation.Latest_translation(), rectangle.Right()),
    //     Intersect(circle_translation.Latest_translation(), rectangle.Bottom()),
    //     Intersect(circle_translation.Latest_translation(), rectangle.Left())
    // };
    std::vector<Line> rectangle_line
    {
        rectangle.Top(),
        rectangle.Right(),
        rectangle.Bottom(),
        rectangle.Left()
    };
    std::vector<float> ts = {0, 0, 0, 0};
    float t_dummy;
    for (unsigned int i = 0; i < 4; i++)
        Intersect(circle_translation.Latest_translation(), ts.at(i), rectangle_line.at(i), t_dummy);

    unsigned int min_t_index = std::distance(ts.begin(), std::min_element(ts.begin(), ts.end()));

    if (ts.at(min_t_index) == 2)
        return;

    // collision solving:

    // ts.at(min_t_index) = std::ceilf(ts.at(min_t_index) * 10) / 10;
    // moving_circle.Translate(-ts.at(min_t_index) * circle_translation.Displacement());
    ts.at(min_t_index) = std::truncf(ts.at(min_t_index) * 10) / 10;
    moving_circle.Translate((ts.at(min_t_index) - 1) * circle_translation.Displacement());
    // circle_translation.Translate_to(moving_circle.Center());
    // circle_translation.Stop(); return; // no need to compensate collision resolution in Translation when stopping

    // reflection:
    
    Vector normal_unit = Vector(0, 0);

    if (min_t_index % 2 == 0)
        normal_unit = Vector(0, 1);
    else
        normal_unit = Vector(1, 0);

    circle_translation.Reflected_by(moving_circle.Center(), normal_unit);
}

// circle1 is the moving circle
// circle2 is initially nonmoving, moved by circle1 if they collide
void Collision::Reflect_circle_circle(Circle &circle1, Translation &translation1, Circle &circle2, Translation &translation2)
{
    float t = Intersect(circle1, translation1, circle2, translation2);

    if (t == 2)
        return;

    // collision solving

    t = std::truncf(t * 10) / 10;

    circle1.Translate((t - 1) * translation1.Displacement());
    // translation1.Translate_to(circle1.Center());
    
    circle2.Translate((t - 1) * translation2.Displacement());
    // translation2.Translate_to(circle2.Center());

    // reflection

    Vector normal_unit = (circle1.Center() - circle2.Center()).Unit();
    translation1.Reflected_by(circle1.Center(), normal_unit);
    translation2.Reflected_by(circle2.Center(), -normal_unit);

    // stop
    // translation1.Stop();
    // translation2.Stop();
}

// assign 0 to 1 to t1 and t2 if intersect
// assign 2 to t1 and t2 if not intersect
void Collision::Intersect(const Line &line1, float &t1, const Line &line2, float &t2)
{
    Vector v = line1.End() - line1.Start();
    Vector s = line2.End() - line2.Start();
    Vector d = line2.Start() - line1.Start();

    float denom = Vector::Dot(v, Matrix(0, -1, 1, 0) * s);

    if (denom == 0)
    {
        t1 = 2;
        t2 = 2;
        return;
    }

    float t1_num = Vector::Dot(d, Matrix(0, -1, 1, 0) * s);

    // t1 < 0
    if ((denom > 0 && t1_num < 0) || (denom < 0 && t1_num > 0))
    {
        t1 = 2;
        t2 = 2;
        return;
    }

    // t1 > 1, where t1_num and denom same sign
    if ((denom > 0 && denom < t1_num) || (denom < 0 && denom > t1_num))
    {
        t1 = 2;
        t2 = 2;
        return;
    }

    // repeat the process for t2

    float t2_num = Vector::Dot(d, Matrix(0, -1, 1, 0) * v);

    // t2 < 0
    if ((denom > 0 && t2_num < 0) || (denom < 0 && t2_num > 0))
    {
        t1 = 2;
        t2 = 2;
        return;
    }

    // t2 > 1, where t2_num and denom same sign
    if ((denom > 0 && denom < t2_num) || (denom < 0 && denom > t2_num))
    {
        t1 = 2;
        t2 = 2;
        return;
    }

    t1 = t1_num / denom;
    t2 = t2_num / denom;
}

// return 0 to 1 if intersect
// return 2 if not intersect
float Collision::Intersect(const Line& line, const Circle& circle)
{
    Vector X = line.Start() - circle.Center();
    Vector Y = line.End() - line.Start();

    float a = Vector::Dot(Y, Y);
    float b = 2 * Vector::Dot(X, Y);
    float c = Vector::Dot(X, X) - circle.Radius() * circle.Radius();

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 2;
    } else {
        discriminant = sqrtf(discriminant);

        // Compute min and max solutions of t
        float t_min = (-b - discriminant) / (2 * a);
        float t_max = (-b + discriminant) / (2 * a);

        // Check whether either t is within bounds of segment
        if (t_min >= 0 && t_min <= 1) {
            return t_min;
        } else if (t_max >= 0 && t_max <= 1) {
            return t_max;
        } else {
            return 2;
        }
    }
}

// return 0 to 1 if intersect
// return 2 if not intersect
float Collision::Intersect(const Circle &circle1, const Translation &translation1, const Circle &circle2, const Translation &translation2)
{
    Vector c1 = translation1.Latest_translation().Start();
    Vector c2 = translation2.Latest_translation().Start();
    Vector v1 = translation1.Displacement();
    Vector v2 = translation2.Displacement();

    Vector c = c2 - c1;
    Vector v = v2 - v1;
    float r = circle1.Radius() + circle2.Radius();

    float a = v.Magsq();

    float discriminant_square = Square(r) * a - Square(Vector::Dot(c, Matrix(0, 1, -1, 0) * v));

    if (discriminant_square < 0)
        return 2;

    float discriminant = sqrtf(discriminant_square);

    float b = Vector::Dot(c, v);

    std::vector<float> t {2, 2};

    float t1 = (-b + discriminant) / a;

    if (t1 >= 0 && t1 <= 1)
        t.front() = t1;

    float t2 = (-b - discriminant) / a;

    if (t2 >= 0 && t2 <= 1)
        t.back() = t2;

    return *std::min_element(t.begin(), t.end());
}

Translation::Translation(const Vector& initial_position)
:
    translation_step_count{Param::translation_step},
    displacement{0, 0},
    latest_translation{initial_position, initial_position}
{}

void Translation::Reset(const Vector &start, const Vector &end)
{
    translation_step_count = 0;

    displacement = (end - start) / Param::translation_step;

    latest_translation = Line(start, start);
}

bool Translation::Finish() const
{
    return translation_step_count == Param::translation_step;
}

void Translation::Next()
{
    translation_step_count++;

    Vector new_start = latest_translation.End();
    Vector new_end = new_start + displacement;

    latest_translation = Line(new_start, new_end);
}

const Vector Translation::Displacement() const
{
    if (translation_step_count != Param::translation_step)
        return displacement;

    return Vector(0, 0);
}

void Translation::Reflected_by(const Vector &start, const Vector &normal_unit)
{
    if (Finish())
    {
        translation_step_count = 0;

        displacement = Param::reach_radius / Param::translation_step * normal_unit;
    }
    else
    {
        Vector normal_displacement = Vector::Dot(displacement, normal_unit) * normal_unit;
        Vector tangential_displacement = displacement - normal_displacement;

        displacement = tangential_displacement - normal_displacement;
    }

    latest_translation = Line(start, start);
}

Line Translation::Latest_translation() const
{
    return latest_translation;
}

void Translation::Stop()
{
    translation_step_count = Param::translation_step;
}

// void Translation::Translate_to(const Vector& position)
// {
//     latest_translation = Line(position, position);
// }