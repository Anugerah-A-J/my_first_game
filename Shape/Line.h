#include "../Math/Vector.h"
#pragma once

class Line
{
public:
    Line(const Vector& start, const Vector& end);

    const Vector& get_start() const;
    const Vector& get_end() const;

    void translate(const Vector& v);
private:
    Vector start;
    Vector end;
};