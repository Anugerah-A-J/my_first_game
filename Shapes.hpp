#include "Vector.hpp"
#pragma once

struct Line
{
    Vector start;
    Vector end;

    Line(const Vector& start, const Vector& end)
    :
        start{start}, end{end}
    {};

    void translate(const Vector& displacement)
    {
        start += displacement;
        end += displacement;
    };
};

struct Rectangle
{
    Vector start;
    Vector end;
    
    Rectangle(float x, float y, float w, float h)
    :
        start{x, y},
        end{start + Vector(w, h)}
    {};
};

struct Circle
{
    Vector center;
    float radius;

    Circle(float cx, float cy, float r)
    :
        center{cx, cy}, radius{r}
    {};
};

struct Triangle
{
    Vector vertex_1;
    Vector vertex_2;
    Vector vertex_3;

    Triangle(const Vector& vertex_1, const Vector& vertex_2, const Vector& vertex_3)
    :
        vertex_1{vertex_1}, vertex_2{vertex_2}, vertex_3{vertex_3}
    {};

    void translate(const Vector& displacement)
    {
        vertex_1 += displacement;
        vertex_2 += displacement;
        vertex_3 += displacement;
    };
};