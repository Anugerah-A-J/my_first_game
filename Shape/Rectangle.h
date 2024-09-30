#include "../Math/Vector.h"
#include "../Shape/Line.h"
#pragma once

class Rectangle
{
public:
    Rectangle(float ox, float oy, float w, float h);

    const Vector& get_origin() const;
    const Vector& get_size() const;
    const Vector get_max() const;
    Line top() const;
    Line right() const;
    Line bottom() const;
    Line left() const;
    
    void translate(const Vector& how_much);
    void add_to_size(const Vector& how_much);
private:
    float nonnegative(float f);
    Vector origin;
    Vector size;
};