#include "../Math/Vector.h"
#pragma once

class Circle
{
public:
    Circle(float cx, float cy, float r);

    const Vector& get_center() const;
    float get_radius() const;
    
    void translate(const Vector& v);
    void add_radius(float r);
    void set_center(const Vector& v);
private:
    float nonnegative(float f);
    Vector center;
    float radius;
};