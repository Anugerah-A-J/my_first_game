#include "Collision.h"

void Collision::circle_vs_rectangle(Circle& circle, Rectangle& rectangle, const Line& circle_relative_velocity)
{
}

bool Collision::intersect(const Line &line1, const Line &line2, float &t)
{
    Vector A = line1.get_end() - line1.get_start();
    Vector B = line2.get_end() - line2.get_start();
    Vector C = line1.get_start() - line2.get_start();

    float numerator = B.get_y() * C.get_x() - B.get_x() * C.get_y();
    float denominator = A.get_y() * B.get_x() - A.get_x() * B.get_y();

    return false;
}
