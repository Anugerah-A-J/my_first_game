#include "Vector.h"
#include <array>
#pragma once

class Matrix
{
public:
    Matrix(float f1, float f2, float f3, float f4);
    const Vector& get_row(unsigned int ui) const;
private:
    std::array<Vector, 2> rows;
};

Vector operator*(const Matrix& m, const Vector& v);