#include "Math.h"
#pragma once

class Line
{
public:
    Line(const Vector& start, const Vector& end);
    const Vector& get_start() const;
    const Vector& get_end() const;
private:
    Vector start;
    Vector end;
};