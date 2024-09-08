#include "Magenta_pawn.h"
#include <allegro5/allegro_primitives.h>

Magenta_pawn::Magenta_pawn(float cx, float cy):
    cx{cx},
    cy{cy}
{
    move_step_count = 0;
    dx = 0;
    dy = 0;
}

void Magenta_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, al_map_rgb_f(red, green, blue));
}

bool Magenta_pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Magenta_pawn::get_cx() const
{
    return cx;
}

float Magenta_pawn::get_cy() const
{
    return cy;
}

void Magenta_pawn::move()
{
    if (move_step_count == Parameter::move_step)
        return;
    
    move_step_count ++;
    cx += dx;
    cy += dy;
}

void Magenta_pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}

unsigned int Magenta_pawn::get_move_step_count() const
{
    return move_step_count;
}

void Magenta_pawn::update_dxdy(float x_finish, float y_finish)
{
    dx = (x_finish - cx) / Parameter::move_step;
    dy = (y_finish - cy) / Parameter::move_step;
}

void Magenta_pawn::stop()
{
    move_step_count = Parameter::move_step;
}

float Magenta_pawn::get_dx() const
{
    return dx;
}

float Magenta_pawn::get_dy() const
{
    return dy;
}

bool Magenta_pawn::is_dead()
{
    if (
        red > Parameter::window_red ||
        green > Parameter::window_green ||
        blue > Parameter::window_blue
    )
        return false;

    red = Parameter::window_red;
    green = Parameter::window_green;
    blue = Parameter::window_blue;
    
    return true;
}

void Magenta_pawn::dying()
{
    if (red > Parameter::window_red)
        red -= 0.1;

    if (green > Parameter::window_green)
        green -= 0.1;

    if (blue > Parameter::window_blue)
        blue -= 0.1;
}