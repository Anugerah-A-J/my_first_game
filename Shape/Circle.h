#include "../Math/Vector.h"
#pragma once

class Circle
{
public:
    Circle(float cx, float cy, float r);

    const Vector& get_center() const;
    float get_radius() const;
    
    void translate(const Vector& how_much);
    void translate_to(const Vector& destination);
    void add_to_radius(float how_much);
private:
    float nonnegative(float f);
    Vector center;
    float radius;
};