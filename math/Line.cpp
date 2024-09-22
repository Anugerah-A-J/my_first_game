#include "Line.h"

Line::Line(const Vector& start, const Vector& end)
:
    start{start},
    end{end}
{}

const Vector& Line::get_start() const
{
    return start;
}

const Vector& Line::get_end() const
{
    return end;
}