#include "Pawn.h"
#include <allegro5/allegro_primitives.h>

Pawn::Pawn(float cx, float cy, float red, float green, float blue):
    cx{cx},
    cy{cy},
    red{red},
    green{green},
    blue{blue}
{
}

void Pawn::draw() const
{
    al_draw_filled_circle(cx, cy, r, al_map_rgb_f(red, green, blue));
}

bool Pawn::pointed_by(int x, int y) const
{
    float rx{ x - cx };
    float ry{ y - cy };

    return rx * rx + ry * ry <= r * r;
}

float Pawn::get_cx() const
{
    return cx;
}

float Pawn::get_cy() const
{
    return cy;
}

void Pawn::move()
{
    if (move_step_count == Parameter::move_step)
        return;
    
    move_step_count ++;
    cx += dx;
    cy += dy;
}

void Pawn::move(float dx, float dy)
{
    cx += dx;
    cy += dy;
}

void Pawn::update_dxdy(float x_finish, float y_finish)
{
    dx = (x_finish - cx) / Parameter::move_step;
    dy = (y_finish - cy) / Parameter::move_step;
}

void Pawn::stop()
{
    move_step_count = Parameter::move_step;
}

float Pawn::get_dx() const
{
    return dx;
}

float Pawn::get_dy() const
{
    return dy;
}

unsigned int Pawn::get_move_step_count() const
{
    return move_step_count;
}

bool Pawn::is_dead()
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

void Pawn::die()
{
    if (is_dead())
        return;

    red += 0.1 * (Parameter::window_red - red);
    green += 0.1 * (Parameter::window_green - green);
    blue += 0.1 * (Parameter::window_blue - blue);
}