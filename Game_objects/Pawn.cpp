#include "Pawn.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>

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

    if (finish_moving())
        stop();
}

void Pawn::retreat(float f)
{
    circle_shape.translate(-d * f);
}

void Pawn::update_d(const Vector &start, const Vector &end)
{
    d = end - start / Parameter::move_step();
}

void Pawn::stop()
{
    move_step_count = Parameter::move_step();
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
}