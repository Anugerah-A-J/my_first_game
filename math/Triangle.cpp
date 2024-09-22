#include "Triangle.h"

Triangle::Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3)
:
    vertices{vertex_1, vertex_2, vertex_3}
{}

const Vector& Triangle::get_vertex(unsigned int ui) const
{
    return vertices.at(ui - 1);
}

void Triangle::add_to_vertex(unsigned ui, const Vector& vertex)
{
    vertices.at(ui - 1) += vertex;
}

void Triangle::multiply_to_vertex(unsigned ui, float f)
{
    vertices.at(ui - 1) *= f;
}

void Triangle::translate(const Vector& v)
{
    for(Vector& vertex : vertices)
        vertex += v; 
}