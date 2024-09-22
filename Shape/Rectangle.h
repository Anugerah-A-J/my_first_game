#include "../Math/Vector.h"
#pragma once

class Rectangle
{
public:
    Rectangle(float o1, float o2, float w, float h);
    const Vector& get_origin() const;
    const Vector& get_size() const;
    const Vector& get_max() const;
    void translate(const Vector& v);
private:
    float validate_size(float f);
    Vector origin;
    Vector size;
};