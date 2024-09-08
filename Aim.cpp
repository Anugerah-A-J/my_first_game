#include "Aim.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Aim::Aim():
    cx{0}, cy{0},
    r{Parameter::reach_radius},
    x{0}, y{0},
    x1{0}, y1{0},
    x2{0}, y2{0},
    x3{0}, y3{0},
    color{al_map_rgb_f(1, 0, 1)},
    thickness{Parameter::line_width},
    visible{false}
{
}

void Aim::draw() const
{
    if (!visible)
        return;
    
    al_draw_circle(cx, cy, r, color, thickness);
    al_draw_triangle(x1, y1, x2, y2, x3, y3, color, thickness);
    al_draw_line(cx, cy, x, y, color, thickness);
}

void Aim::set_center(float cx, float cy)
{
    this->cx = cx;
    this->cy = cy;
}

void Aim::update_xy(float mouse_x, float mouse_y)
{
    if (!visible)
        return;

    float vx {mouse_x - cx};
    float vy {mouse_y - cy};
    float v_mag {sqrtf(vx * vx + vy * vy)};

    x = cx - vx / v_mag * r;
    y = cy - vy / v_mag * r;

    x1 = cx + vx / v_mag * Parameter::radius * 2;
    y1 = cy + vy / v_mag * Parameter::radius * 2;

    float temp_x {x1 + vx / v_mag * Parameter::triangle_height};
    float temp_y {y1 + vy / v_mag * Parameter::triangle_height};

    x2 = temp_x + vy / v_mag * Parameter::triangle_height / Parameter::sqrt_3;
    y2 = temp_y - vx / v_mag * Parameter::triangle_height / Parameter::sqrt_3;

    x3 = temp_x - vy / v_mag * Parameter::triangle_height / Parameter::sqrt_3;
    y3 = temp_y + vx / v_mag * Parameter::triangle_height / Parameter::sqrt_3;
}

float Aim::get_cx() const
{
    return cx;
}

float Aim::get_cy() const
{
    return cy;
}

float Aim::get_x() const
{
    return x;
}

float Aim::get_y() const
{
    return y;
}

void Aim::magenta()
{
    color = al_map_rgb_f(1, 0, 1);
}

void Aim::cyan()
{
    color = al_map_rgb_f(0, 1, 1);
}

void Aim::show()
{
    visible = true;
}

void Aim::hide()
{
    visible = false;
}

bool Aim::get_visible() const
{
    return visible;
}