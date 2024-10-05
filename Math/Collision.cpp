#include "Collision.h"
#include "math.h"
#include <cmath>
#include <algorithm>

void Collision::operator()(std::vector<Pawn *> &dying_pawns, Pawn &pawn, const Fence &f)
{
    float t = circle_inside_rectangle(pawn.get_shape(), f.get_shape(), pawn.get_velocity());

    if (t == 2)
        return;
    
    pawn.retreat(1 - t);
    pawn.stop();
    dying_pawns.emplace_back(&pawn);
}

float Collision::circle_vs_circle(const Circle &moving_circle, const Circle &nonmoving_circle, const Line &velocity)
{
    Circle circle = nonmoving_circle;
    circle.add_to_radius(moving_circle.get_radius());

    return intersect(velocity, circle);
}

float Collision::circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity)
{
    Circle top_left = moving_circle;
    Circle top_right = moving_circle;
    Circle bottom_right = moving_circle;
    Circle bottom_left = moving_circle;

    Line top = nonmoving_rectangle.top();
    Line right = nonmoving_rectangle.right();
    Line bottom = nonmoving_rectangle.bottom();
    Line left = nonmoving_rectangle.left();

    top_left.translate_to(top.get_start());
    top_right.translate_to(top.get_end());
    bottom_right.translate_to(bottom.get_start());
    bottom_left.translate_to(bottom.get_end());

    top.translate(Vector(0, -moving_circle.get_radius()));
    right.translate(Vector(moving_circle.get_radius(), 0));
    bottom.translate(Vector(0, moving_circle.get_radius()));
    left.translate(Vector(-moving_circle.get_radius(), 0));

    std::vector<float> ts;

    ts.emplace_back(intersect(velocity, top));
    ts.emplace_back(intersect(velocity, right));
    ts.emplace_back(intersect(velocity, bottom));
    ts.emplace_back(intersect(velocity, left));

    ts.emplace_back(intersect(velocity, top_left));
    ts.emplace_back(intersect(velocity, top_right));
    ts.emplace_back(intersect(velocity, bottom_right));
    ts.emplace_back(intersect(velocity, bottom_left));

    return *std::min_element(ts.begin(), ts.end());
}

float Collision::circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity)
{
    Rectangle rectangle = nonmoving_rectangle;
    rectangle.translate(Vector(moving_circle.get_radius()));
    rectangle.add_to_size(-2 * Vector(moving_circle.get_radius()));

    std::vector<float> ts;

    ts.emplace_back(intersect(velocity, rectangle.top()));
    ts.emplace_back(intersect(velocity, rectangle.right()));
    ts.emplace_back(intersect(velocity, rectangle.bottom()));
    ts.emplace_back(intersect(velocity, rectangle.left()));

    return *std::min_element(ts.begin(), ts.end());
}

float Collision::intersect(const Line& line1, const Line& line2)
{
    Vector A = line1.get_end() - line1.get_start();
    Vector B = line2.get_end() - line2.get_start();
    Vector C = line1.get_start() - line2.get_start();

    float numerator = B.get_y() * C.get_x() - B.get_x() * C.get_y();
    float denominator = A.get_y() * B.get_x() - A.get_x() * B.get_y();
    
    if (denominator > 0 && numerator < 0)
        return 2;
    
    if (denominator > 0 && numerator > denominator)
        return 2;

    if (denominator < 0 && numerator > 0)
        return 2;

    if (denominator < 0 && numerator < denominator)
        return 2;

    if (equal(denominator, 0, 0.05f))
        return 2;

    return numerator / denominator;
}

float Collision::intersect(const Line& line, const Circle& circle)
{
    Vector X = line.get_start() - circle.get_center();
    Vector Y = line.get_end() - line.get_start();

    float a = dot(Y, Y);
    float b = 2 * dot(X, Y);
    float c = dot(X, X) - circle.get_radius() * circle.get_radius();

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return 2;
    }
    else
    {
        discriminant = sqrtf(discriminant);

        // Compute min and max solutions of t
        float t_min = (-b - discriminant) / (2 * a);
        float t_max = (-b + discriminant) / (2 * a);
        
        // Check whether either t is within bounds of segment
        if (t_min >= 0 && t_min <= 1)
        {
            return t_min;
        }
        else if (t_max >= 0 && t_max <= 1)
        {
            return t_max;
        }
        else
        {
            return 2;
        }
    }
}