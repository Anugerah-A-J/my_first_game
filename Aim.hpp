#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "Shapes.hpp"
#include "param.hpp"
#pragma once

struct Aim
{
    void draw() const
    {
        if (!visible)
            return;
        
        al_draw_circle(
            shape_circle.center.x,
            shape_circle.center.y,
            shape_circle.radius,
            color,
            thickness
        );
        al_draw_triangle(
            shape_triangle.vertex_1.x,
            shape_triangle.vertex_1.y,
            shape_triangle.vertex_2.x,
            shape_triangle.vertex_2.y,
            shape_triangle.vertex_3.x,
            shape_triangle.vertex_3.y,
            color,
            thickness
        );
        al_draw_line(
            shape_circle.center.x,
            shape_circle.center.y,
            end_point.x,
            end_point.y,
            color,
            thickness
        );
    };

    Circle shape_circle = Circle(0, 0, param::reach_radius);

    Vector end_point = Vector(0, 0);
    
    Triangle shape_triangle = Triangle(Vector(0, 0), Vector(0, 0), Vector(0, 0));
    
    ALLEGRO_COLOR color = param::magenta;
    
    float thickness = param::line_width;
    
    bool visible = false;
};