#include "Cyan_pawn.h"
#include <allegro5/allegro_primitives.h>
// #include <iostream>

Cyan_pawn::Cyan_pawn(float cx, float cy):
    cx{cx},
    cy{cy}
{
    move_step_count = 0;
    dx = 0;
    dy = 0;
}

void Cyan_pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, al_map_rgb_f(red, green, blue));
}

bool Cyan_pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Cyan_pawn::get_cx() const
{
    return cx;
}

float Cyan_pawn::get_cy() const
{
    return cy;
}

void Cyan_pawn::move()
{
    if (move_step_count == Parameter::move_step)
        return;
    
    move_step_count ++;
    cx += dx;
    cy += dy;
}

void Cyan_pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}

void Cyan_pawn::update_dxdy(float x_finish, float y_finish)
{
    dx = (x_finish - cx) / Parameter::move_step;
    dy = (y_finish - cy) / Parameter::move_step;
}

void Cyan_pawn::stop()
{
    move_step_count = Parameter::move_step;
}

float Cyan_pawn::get_dx() const
{
    return dx;
}

float Cyan_pawn::get_dy() const
{
    return dy;
}

bool Cyan_pawn::is_dead()
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

void Cyan_pawn::dying()
{
    if (!is_dying)
        return;
        
    if (red > Parameter::window_red)
        red -= 0.1;

    if (green > Parameter::window_green)
        green -= 0.1;

    if (blue > Parameter::window_blue)
        blue -= 0.1;
}

void Cyan_pawn::trigger_dying()
{
    is_dying = true;
}