#include <cmath>
#ifndef INTERSECT_H
#define INTERSECT_H

#pragma once

class Intersect
{
public:
    static bool line_circle(float x, float y, float dx, float dy, float cx, float cy, float r)
    {
        // Compute X, Y, a, b, c as per equations
        float xcx {x - cx};
        float ycy {y - cy};
        float a {dot(-dx, -dy, -dx, -dy)};
        float b {2 * dot(xcx, ycy, -dx, -dy)};
        float c {dot(xcx, ycy, xcx, ycy) - r * r};
        
        // Compute discriminant
        float disc {b * b - 4 * a * c};

        if (disc < 0)
        {
            return false;
        }
        else
        {
            disc = std::sqrt(disc);
            
            // Compute min and max solutions of t
            float t_min {(-b - disc) / (2 * a)};
            float t_max {(-b + disc) / (2 * a)};
            float out_t {0};

            // Check whether either t is within bounds of segment
            if (t_min >= 0 && t_min <= 1)
            {
                out_t = t_min;
                return true;
            }
            else if (t_max >= 0 && t_max <= 1)
            {
                out_t = t_max;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
private:
    static float dot(float x1, float y1, float x2, float y2)
    {
        return x1 * x2 + y1 * y2;
    }
};

#endif