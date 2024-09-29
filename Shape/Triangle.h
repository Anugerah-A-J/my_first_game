#include "../Math/Vector.h"
#include <array>
#pragma once

class Triangle
{
public:
    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3);

    const Vector& get_vertex(unsigned int index) const;
    
    void add_to_vertex(unsigned index, const Vector& how_much);
    void multiply_to_vertex(unsigned index, float how_much);
    void translate(const Vector& how_much);
private:
    std::array<Vector, 3> vertices;
};