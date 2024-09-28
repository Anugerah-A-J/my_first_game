#include "../Math/Vector.h"
#include "../Shape/Line.h"
#pragma once

class Rectangle
{
public:
    Rectangle(float ox, float oy, float w, float h);

    const Vector& get_origin() const;
    const Vector& get_size() const;
    const Vector& get_max() const;
    Line top() const;
    Line right() const;
    Line bottom() const;
    Line left() const;
    
    void translate(const Vector& v);
    void add_size(const Vector& v);
private:
    float validate_size(float f);
    Vector origin;
    Vector size;
};