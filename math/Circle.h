#include "Math.h"
#pragma once

class Circle
{
public:
    Circle(float cx, float cy, float r);
    const Vector& get_center() const;
    float get_radius() const;
    void translate(const Vector& v);
private:
    float validate_radius(float f);
    Vector center;
    float radius;
};