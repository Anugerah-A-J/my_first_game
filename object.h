#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "geometry.h"
#include "param.h"
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

struct Clipper
{
    void draw() const
    {
        al_draw_filled_rectangle(
            left.start.x,
            left.start.y,
            left.end.x,
            left.end.y,
            color
        );

        al_draw_filled_rectangle(
            top.start.x,
            top.start.y,
            top.end.x,
            top.end.y,
            color
        );

        al_draw_filled_rectangle(
            right.start.x,
            right.start.y,
            right.end.x,
            right.end.y,
            color
        );

        al_draw_filled_rectangle(
            bottom.start.x,
            bottom.start.y,
            bottom.end.x,
            bottom.end.y,
            color
        );
    };

    Rectangle left = Rectangle(
        0,
        0,
        2 * param::space,
        param::window_height
    );
    
    Rectangle top = Rectangle(
        0,
        0,
        param::window_width,
        param::space
    );
    
    Rectangle right = Rectangle(
        param::window_width - 2 * param::space,
        0,
        2 * param::space,
        param::window_height
    );
    
    Rectangle bottom = Rectangle(
        0,
        param::window_height - param::space,
        param::window_width,
        param::space
    );
    
    ALLEGRO_COLOR color = param::black;
};

struct Fence
{
    void draw() const
    {
        al_draw_rectangle(
            shape.start.x,
            shape.start.y,
            shape.end.x,
            shape.end.y,
            color,
            thickness
        );
    };

    Rectangle shape = Rectangle(
        2 * param::space,
        param::space,
        param::window_width - 4 * param::space,
        param::window_height - 2 * param::space
    );
    
    ALLEGRO_COLOR color = param::red;

    float thickness = param::line_width;
};