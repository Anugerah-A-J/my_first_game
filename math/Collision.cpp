#include "Collision.h"
#include "math.h"
#include <cmath>

void Collision::circle_vs_circle(Circle& moving_circle, Circle& nonmoving_circle, Line& velocity){;}
void Collision::circle_vs_rectangle(Circle& moving_circle, Rectangle& nonmoving_rectangle, const Line& velocity){;}
void Collision::circle_inside_rectangle(Circle& moving_circle, Rectangle& nonmoving_rectangle, const Line& velocity){;}

bool Collision::intersect(const Line& line1, const Line& line2, float& t)
{
    Vector A = line1.get_end() - line1.get_start();
    Vector B = line2.get_end() - line2.get_start();
    Vector C = line1.get_start() - line2.get_start();

    float numerator = B.get_y() * C.get_x() - B.get_x() * C.get_y();
    float denominator = A.get_y() * B.get_x() - A.get_x() * B.get_y();
    
    if (denominator > 0 && numerator < 0)
        return false;
    
    if (denominator > 0 && numerator > denominator)
        return false;

    if (denominator < 0 && numerator > 0)
        return false;

    if (denominator < 0 && numerator < denominator)
        return false;

    if (equal(denominator, 0, 0.05f))
        return false;

    t = numerator / denominator;

    return true;
}

bool Collision::intersect(const Line& line, const Circle& circle, float& t)
{
    Vector X = line.get_start() - circle.get_center();
    Vector Y = line.get_end() - line.get_start();

    float a = dot(Y, Y);
    float b = 2 * dot(X, Y);
    float c = dot(X, X) - circle.get_radius() * circle.get_radius();

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return false;
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
            t = t_min;
            return true;
        }
        else if (t_max >= 0 && t_max <= 1)
        {
            t = t_max;
            return true;
        }
        else
        {
            return false;
        }
    }
}