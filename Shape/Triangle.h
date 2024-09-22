#include "../Math/Vector.h"
#include <array>
#pragma once

class Triangle
{
public:
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3);
    const Vector& get_vertex(unsigned int ui) const;
    void add_to_vertex(unsigned ui, const Vector& vertex);
    void multiply_to_vertex(unsigned ui, float f);
    void translate(const Vector& v);
private:
    std::array<Vector, 3> vertices;
};