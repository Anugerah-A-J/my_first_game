#include "Collision.hpp"
#include <algorithm>

float Collision::circle_vs_circle(const Circle& moving_circle, const Circle& nonmoving_circle, const Line& velocity)
{
    Circle circle = nonmoving_circle;
    circle.radius += moving_circle.radius;

    return intersect(velocity, circle);
};

float Collision::circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity)
{
    Line top = nonmoving_rectangle.top();
    Line right = nonmoving_rectangle.right();
    Line bottom = nonmoving_rectangle.bottom();
    Line left = nonmoving_rectangle.left();

    Circle top_left = moving_circle;
    Circle top_right = moving_circle;
    Circle bottom_right = moving_circle;
    Circle bottom_left = moving_circle;

    top_left.center = top.start;
    top_right.center = top.end;
    bottom_right.center = bottom.start;
    bottom_left.center = bottom.end;

    top.translate(Vector(0, -moving_circle.radius));
    right.translate(Vector(moving_circle.radius, 0));
    bottom.translate(Vector(0, moving_circle.radius));
    left.translate(Vector(-moving_circle.radius, 0));

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
};

float Collision::circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity)
{
    Rectangle rectangle = nonmoving_rectangle;
    rectangle.translate(Vector(moving_circle.radius, moving_circle.radius));
    rectangle.end -= 2 * Vector(moving_circle.radius, moving_circle.radius);

    std::vector<float> ts;

    ts.emplace_back(intersect(velocity, rectangle.top()));
    ts.emplace_back(intersect(velocity, rectangle.right()));
    ts.emplace_back(intersect(velocity, rectangle.bottom()));
    ts.emplace_back(intersect(velocity, rectangle.left()));

    return *std::min_element(ts.begin(), ts.end());
};

float Collision::intersect(const Line& line1, const Line& line2)
{
    Vector A = line1.end - line1.start;
    Vector B = line2.end - line2.start;
    Vector C = line1.start - line2.start;

    float t_numerator = B.y * C.x - B.x * C.y;
    float u_numerator = C.y * A.x - C.x * A.y;
    float denominator = A.y * B.x - A.x * B.y;

    // std::cout << "    t num: " << t_numerator << "\n";
    // std::cout << "    u num: " << u_numerator << "\n";
    // std::cout << "    denom: " << denominator << "\n";
    // std::cout << "    t: " << t_numerator / denominator << "\n";
    // std::cout << "    u: " << u_numerator / denominator << "\n";

    // // t < 0 and u < 0
    // if (denominator > 0 && (t_numerator < 0 || u_numerator < 0))
    //     return 2;
    // if (denominator < 0 && (t_numerator > 0 || u_numerator > 0))
    //     return 2;

    // // t > 1 and u > 1
    // if (denominator > 0 && (t_numerator > denominator || u_numerator > denominator))
    //     return 2;
    // if (denominator < 0 && (t_numerator < denominator || u_numerator < denominator))
    //     return 2;

    // if (equal(denominator, 0, 0.05f))
    if (denominator == 0)
        return 2;

    float t = t_numerator / denominator;
    float u = u_numerator / denominator;

    // if (t < 0 || t > 1 || u < 0 || u > 0)
    if (t < 0 || t > 1)
        return 2;

    return t;
};

float Collision::intersect(const Line& line, const Circle& circle)
{
    Vector X = line.start - circle.center;
    Vector Y = line.end - line.start;

    float a = dot(Y, Y);
    float b = 2 * dot(X, Y);
    float c = dot(X, X) - circle.radius * circle.radius;

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
};