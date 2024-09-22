#include "Matrix.h"

Matrix::Matrix(float f1, float f2, float f3, float f4)
:
    rows{Vector(f1, f2), Vector(f3, f4)}
{}

const Vector& Matrix::get_row(unsigned int ui) const
{
    return rows.at(ui - 1);
}

Vector operator*(const Matrix& m, const Vector& v)
{
    return Vector(
        dot(m.get_row(1), v),
        dot(m.get_row(2), v)
    );
}