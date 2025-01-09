#include "Collision.hpp"
#include "Param.hpp"
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

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

Collision::Collision()
:
    t{2}
{}

bool Collision::Earlier_than(const Collision& collision) const
{
    return t < collision.t;
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

    return Intersect_circle_circle(c, v, r);
}

float Collision::Intersect(const Circle& moving_circle, const Translation& translation, Circle& nonmoving_circle)
{
    Vector c1 = translation.Latest().Start();
    Vector c2 = nonmoving_circle.Center();
    Vector v = translation.Latest().Direction();

    Vector c = c2 - c1;
    float r = moving_circle.Radius() + nonmoving_circle.Radius();

    return Intersect_circle_circle(c, v, r);
}

float Collision::Intersect_circle_circle(const Vector& c, const Vector& v, float r)
{
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


Circle_inside_rectangle::Circle_inside_rectangle(Circle &moving_circle, Translation &circle_translation, const Rectangle &nonmoving_rectangle)
:
    Collision{},
    normal_unit{0, 0},
    moving_circle{moving_circle},
    circle_translation{circle_translation},
    nonmoving_rectangle{nonmoving_rectangle}
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

    std::cout << "ts.at(min_t_index) : " << ts.at(min_t_index) << "\n";
    // std::cout << "t : " << t << "\n";

    if (ts.at(min_t_index) == 2)
        return;

    t = ts.at(min_t_index);

    if (min_t_index % 2 == 0)
        normal_unit = Vector(0, 1);
    else
        normal_unit = Vector(1, 0);
}

void Circle_inside_rectangle::Reflect()
{
    if (t == 2)
        return;

    std::cout << "t : " << t << "\n";
    // collision solving: make them don't touch each other. Give space of 1 pixel between them.

    float retreat = t - 1 - 1 / circle_translation.Latest().Length();

    moving_circle.Translate(retreat * circle_translation.Latest().Direction());

    if (circle_translation.Just_finish())
        return;

    circle_translation.Reflected_by(normal_unit);
}

Circle_outside_circle::Circle_outside_circle(Circle &circle_1, Translation &translation_1, Circle &circle_2, Translation &translation_2)
:
    Collision{},
    normal_unit{0, 0},
    circle_1{circle_1},
    translation_1{translation_1},
    circle_2{circle_2},
    translation_2{translation_2}
{
    t = Intersect(circle_1, translation_1, circle_2, translation_2);
}

void Circle_outside_circle::Reflect()
{
    if (t == 2)
        return;

    // collision solving

    if (!translation_1.Finish())
        circle_1.Translate((t - 1 - 1 / translation_1.Latest().Length()) * translation_1.Latest().Direction());

    if (!translation_2.Finish())
        circle_2.Translate((t - 1 - 1 / translation_2.Latest().Length()) * translation_2.Latest().Direction());

    // reflection

    normal_unit = (circle_1.Center() - circle_2.Center()).Unit();

    // translation_1.Stop();
    translation_1.Reflected_by(normal_unit);
    translation_2.Reflected_by(-normal_unit);
}

Circle_outside_rectangle::Circle_outside_rectangle(Circle &moving_circle, Translation &circle_translation, const Rectangle &nonmoving_rectangle)
:
    Collision{},
    normal_unit{0, 0},
    moving_circle{moving_circle},
    circle_translation{circle_translation},
    nonmoving_rectangle{nonmoving_rectangle}
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
    else
        t = ts.at(min_t_index);

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
}

void Circle_outside_rectangle::Reflect()
{
    if (t == 2)
        return;

    // collision solving: make them don't touch each other. Give space of 1 pixel between them.

    float retreat = t - 1 - 1 / circle_translation.Latest().Length();

    moving_circle.Translate(retreat * circle_translation.Latest().Direction());

    if (circle_translation.Just_finish())
        return;

    circle_translation.Reflected_by(normal_unit);
}
