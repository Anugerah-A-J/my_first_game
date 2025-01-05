#include "Shape.hpp"
#include "Param.hpp"
#include <algorithm>
#include <math.h>
#include <vector>

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

void Line::End(const Vector& end)
{
    this->end = end;
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

Vector& Circle::Center()
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

void Collision::Reflect_circle_inside_rectangle(Circle &moving_circle, Translation &circle_translation, const Rectangle &nonmoving_rectangle)
{
    Rectangle rectangle = nonmoving_rectangle;
    rectangle.Translate(Vector(moving_circle.Radius(), moving_circle.Radius()));
    rectangle.Add_size_by(-2 * Vector(moving_circle.Radius(), moving_circle.Radius()));

    std::vector<Line> rectangle_line
    {
        rectangle.Top(),
        rectangle.Right(),
        rectangle.Bottom(),
        rectangle.Left()
    };
    std::vector<float> ts;
    ts.assign(4, 2);
    float t_dummy;
    for (unsigned int i = 0; i < 4; i++)
        Intersect(circle_translation.Latest(), ts.at(i), rectangle_line.at(i), t_dummy);

    unsigned int min_t_index = std::distance(ts.begin(), std::min_element(ts.begin(), ts.end()));

    if (ts.at(min_t_index) == 2)
        return;

    // collision solving: make them don't touch each other. Give space of 1 pixel between them.

    float retreat = ts.at(min_t_index) - 1 - 1 / circle_translation.Latest().Length();

    moving_circle.Translate(retreat * circle_translation.Latest().Direction());

    if (circle_translation.Just_finish())
        return;

    // reflection:
    
    Vector normal_unit = Vector(0, 0);

    if (min_t_index % 2 == 0)
        normal_unit = Vector(0, 1);
    else
        normal_unit = Vector(1, 0);

    circle_translation.Reflected_by(normal_unit);
}

void Collision::Reflect_circle_circle(Circle &circle_1, Translation &translation_1, Circle &circle_2, Translation &translation_2)
{
    float t = Intersect(circle_1, translation_1, circle_2, translation_2);

    if (t == 2)
        return;

    // collision solving

    if (!translation_1.Finish())
        circle_1.Translate((t - 1 - 1 / translation_1.Latest().Length()) * translation_1.Latest().Direction());
    
    if (!translation_2.Finish())
        circle_2.Translate((t - 1 - 1 / translation_2.Latest().Length()) * translation_2.Latest().Direction());

    // reflection

    Vector normal_unit = (circle_1.Center() - circle_2.Center()).Unit();

    // translation_1.Stop();
    translation_1.Reflected_by(normal_unit);
    translation_2.Reflected_by(-normal_unit);
}

void Collision::Reflect_circle_rectangle(Circle &moving_circle, Translation &circle_translation, const Rectangle &nonmoving_rectangle)
{
    Circle top_left = moving_circle;
    Circle top_right = moving_circle;
    Circle bottom_left = moving_circle;
    Circle bottom_right = moving_circle;

    top_left.Center(nonmoving_rectangle.Top_left());
    top_right.Center(nonmoving_rectangle.Top_right());
    bottom_left.Center(nonmoving_rectangle.Bottom_left());
    bottom_right.Center(nonmoving_rectangle.Bottom_right());

    std::vector<Circle*> rectangle_corner
    {
        &top_left,
        &bottom_left,
        &top_right,
        &bottom_right
    };

    for (Circle* c : rectangle_corner)
        c->Draw(Param::white, Param::line_width);

    std::vector<float> ts;
    ts.assign(8, 2);

    for (unsigned int i = 0; i != 4; i++)
        ts.at(i) = Intersect(moving_circle, circle_translation, *rectangle_corner.at(i));

    Line top = nonmoving_rectangle.Top();
    Line left = nonmoving_rectangle.Left();
    Line bottom = nonmoving_rectangle.Bottom();
    Line right = nonmoving_rectangle.Right();

    top.Translate(Vector(0, -moving_circle.Radius()));
    left.Translate(Vector(-moving_circle.Radius(), 0));
    bottom.Translate(Vector(0, moving_circle.Radius()));
    right.Translate(Vector(moving_circle.Radius(), 0));

    std::vector<const Line*> rectangle_side
    {
        &top,
        &bottom,
        &left,
        &right
    };

    for (const Line* l : rectangle_side)
        l->Draw(Param::white, Param::line_width);

    float t_dum;

    for (unsigned int i = 4; i != ts.size(); i++)
        Intersect(circle_translation.Latest(), ts.at(i), *rectangle_side.at(i - 4), t_dum);

    unsigned int min_t_index = std::distance(ts.begin(), std::min_element(ts.begin(), ts.end()));

    if (ts.at(min_t_index) == 2)
        return;

    // collision solving: make them don't touch each other. Give space of 1 pixel between them.

    float retreat = ts.at(min_t_index) - 1 - 1 / circle_translation.Latest().Length();

    moving_circle.Translate(retreat * circle_translation.Latest().Direction());

    if (circle_translation.Just_finish())
        return;

    // reflection:
    
    Vector normal_unit = Vector(0, 0);

    switch (min_t_index)
    {
    case 0:
    case 1:
        normal_unit = (nonmoving_rectangle.Top_left() - nonmoving_rectangle.Bottom_left()).Unit();
        break;
    case 2:
    case 3:
        normal_unit = (nonmoving_rectangle.Top_right() - nonmoving_rectangle.Bottom_right()).Unit();
        break;
    case 4:
    case 5:
        normal_unit = Vector(0, 1);
        break;
    case 6:
    case 7:
        normal_unit = Vector(1, 0);
        break;
    }

    circle_translation.Reflected_by(normal_unit);
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
float Collision::Intersect(const Circle &circle1, const Translation &translation1, const Circle &circle2, const Translation &translation2)
{
    Vector c1 = translation1.Latest().Start();
    Vector c2 = translation2.Latest().Start();
    Vector v1 = translation1.Latest().Direction();
    Vector v2 = translation2.Latest().Direction();

    Vector c = c2 - c1;
    Vector v = v2 - v1;
    float r = circle1.Radius() + circle2.Radius();

    float a = v.Magsq();

    if (a == 0)
        return 2;

    float discriminant_square = Square(r) * a - Square(Vector::Dot(c, Matrix(0, 1, -1, 0) * v));

    if (discriminant_square < 0)
        return 2;

    float discriminant = sqrtf(discriminant_square);

    float b = Vector::Dot(c, v);

    std::vector<float> t {2, 2};

    float t_num = -b + discriminant;

    if (t_num >= 0 && t_num <= a)
        t.front() = t_num / a;

    t_num = -b - discriminant;

    if (t_num >= 0 && t_num <= a)
        t.back() = t_num / a;

    return *std::min_element(t.begin(), t.end());
}

float Collision::Intersect(const Circle& moving_circle, const Translation& translation, Circle& nonmoving_circle)
{
    return Intersect(
        moving_circle, translation,
        nonmoving_circle, Translation(nonmoving_circle.Center()));
}

Translation::Translation(Vector& start_position)
:
    step_count{Param::translation_step},
    ideal_displacement{0, 0},
    current_position{start_position},
    previous_position{start_position}
{}

void Translation::Reset_all(const Vector &end)
{
    step_count = 0;

    ideal_displacement = (end - previous_position) / Param::translation_step;
}

bool Translation::Finish() const
{
    return step_count == Param::translation_step && current_position == previous_position;
}

bool Translation::Just_finish() const
{
    return step_count == Param::translation_step && current_position != previous_position;
}

void Translation::Move(Circle& circle)
{
    if (Finish())
        return;

    if (Just_finish())
    {
        previous_position = current_position;
        return;
    }

    step_count++;

    previous_position = current_position;
    circle.Translate(ideal_displacement);
}

void Translation::Reflected_by(const Vector &normal_unit)
{
    if (Finish())
    {
        step_count = 0;
        ideal_displacement = Param::reach_radius / Param::translation_step * normal_unit;
    }
    else
    {
        Vector normal_displacement = Vector::Dot(ideal_displacement, normal_unit) * normal_unit;
        Vector tangential_displacement = ideal_displacement - normal_displacement;

        ideal_displacement = tangential_displacement - normal_displacement;
    }
}

Line Translation::Latest() const
{
    return Line(previous_position, current_position);
}

void Translation::Stop()
{
    step_count = Param::translation_step;
}
