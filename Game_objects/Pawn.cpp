#include "Pawn.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include "../Math/math.h"
#include <iostream>

Pawn::Pawn(float cx, float cy, ALLEGRO_COLOR color)
:
    circle_shape{cx, cy, Parameter::radius()},
    color{color}
{
}

void Pawn::draw() const
{
    al_draw_filled_circle(
        circle_shape.get_center().get_x(),
        circle_shape.get_center().get_y(),
        circle_shape.get_radius(),
        color
    );
}

bool Pawn::pointed_by(const Vector& v) const
{
    return (v - circle_shape.get_center()).magsq() <= circle_shape.get_radius() * circle_shape.get_radius();
}

const Vector& Pawn::get_center() const
{
    return circle_shape.get_center();
}

void Pawn::move()
{
    move_step_count ++;
    circle_shape.translate(d);
}

void Pawn::retreat(float f)
{
    circle_shape.translate(-d * f);
}

void Pawn::update_d(const Vector &start, const Vector &end)
{
    d = (end - start) / Parameter::move_step();
    std::cout << "d is updated\n";
}

void Pawn::stop()
{
    move_step_count = Parameter::move_step();
}

void Pawn::die()
{
    color.r = (Parameter::dead_color().r + color.r) * Parameter::color_transformation_ratio();
    color.g = (Parameter::dead_color().g + color.g) * Parameter::color_transformation_ratio();
    color.b = (Parameter::dead_color().b + color.b) * Parameter::color_transformation_ratio();
    color.a = (Parameter::dead_color().a + color.a) * Parameter::color_transformation_ratio();
}

bool Pawn::is_dead()
{
    if(
        equal(color.r, Parameter::dead_color().r, 0.05f) &&
        equal(color.g, Parameter::dead_color().g, 0.05f) &&
        equal(color.b, Parameter::dead_color().b, 0.05f) &&
        equal(color.a, Parameter::dead_color().a, 0.05f)
    ){
        color.r = Parameter::dead_color().r;
        color.g = Parameter::dead_color().g;
        color.b = Parameter::dead_color().b;
        color.a = Parameter::dead_color().a;
        return true;
    }

    return false;
}

bool Pawn::is_dead_immediately_after_finish_moving()
{
    return dead_immediately_after_finish_moving;
}

void Pawn::set_dead_immediately_after_finish_moving(bool b)
{
    dead_immediately_after_finish_moving = b;
}

bool Pawn::finish_moving()
{
    return move_step_count == Parameter::move_step();
}

const Circle &Pawn::get_shape() const
{
    return circle_shape;
}

const Line Pawn::get_velocity() const
{
    return Line(
        circle_shape.get_center() - d,
        circle_shape.get_center()
    );
}

void Pawn::reset_move_step_count()
{
    move_step_count = 0;
    std::cout << "move step count is reset\n";
}