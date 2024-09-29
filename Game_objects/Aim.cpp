#include "Aim.h"
#include <allegro5/allegro_primitives.h>

void Aim::draw() const
{
    if (!visible)
        return;
    
    al_draw_circle(
        circle_shape.get_center().get_x(), circle_shape.get_center().get_y(), circle_shape.get_radius(),
        color, thickness
    );
    al_draw_triangle(
        triangle_shape.get_vertex(1).get_x(), triangle_shape.get_vertex(1).get_y(),
        triangle_shape.get_vertex(2).get_x(), triangle_shape.get_vertex(2).get_y(),
        triangle_shape.get_vertex(3).get_x(), triangle_shape.get_vertex(3).get_y(),
        color, thickness
    );
    al_draw_line(
        circle_shape.get_center().get_x(), circle_shape.get_center().get_y(),
        end_point.get_x(), end_point.get_y(),
        color, thickness
    );
}

void Aim::set_center(const Vector& v)
{
    circle_shape.translate_to(v);
}

void Aim::rotate(Vector v)
{
    v -= circle_shape.get_center();
    v.unit();

    end_point = circle_shape.get_center() - v * circle_shape.get_radius();
    
    triangle_shape.set_vertex(
        1,
        circle_shape.get_center() + v * Parameter::radius() * 2
    );

    Vector temp = triangle_shape.get_vertex(1) + v * Parameter::triangle_height();

    triangle_shape.set_vertex(
        2,
        temp + Matrix(1, 0, 0, -1) * v * Parameter::triangle_height() / Parameter::sqrt_3()
    );

    triangle_shape.set_vertex(
        3,
        temp + Matrix(-1, 0, 0, 1) * v * Parameter::triangle_height() / Parameter::sqrt_3()
    );
}

const Vector& Aim::get_center() const
{
    return circle_shape.get_center();
}

const Vector &Aim::get_endpoint() const
{
    return end_point;
}

void Aim::magenta()
{
    color = Parameter::magenta();
}

void Aim::cyan()
{
    color = Parameter::cyan();
}

void Aim::show()
{
    visible = true;
}

void Aim::hide()
{
    visible = false;
}

bool Aim::is_visible() const
{
    return visible;
}