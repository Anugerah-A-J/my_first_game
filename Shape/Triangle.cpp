#include "Triangle.h"

Triangle::Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3)
:
    vertices{vertex_1, vertex_2, vertex_3}
{}

const Vector& Triangle::get_vertex(unsigned int index) const
{
    return vertices.at(index - 1);
}

void Triangle::set_vertex(unsigned index, const Vector& vertex)
{
    vertices.at(index - 1) = vertex;
}

void Triangle::multiply_to_vertex(unsigned index, float how_much)
{
    vertices.at(index - 1) *= how_much;
}

void Triangle::translate(const Vector& how_much)
{
    for(Vector& vertex : vertices)
        vertex += how_much;
}