#include "Aim.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Aim::Aim():
    cx{0}, cy{0},
    r{4 * Parameter::radius},
    x{0}, y{0},
    x1{0}, y1{0},
    x2{0}, y2{0},
    x3{0}, y3{0},
    color{al_map_rgba_f(1, 0, 1, 1)},
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

    float dx {mouse_x - cx};
    float dy {mouse_y - cy};
    float dr {sqrtf(dx * dx + dy * dy)};

    x = (cx - dx) / dr * r;
    y = (cy - dy) / dr * r;

    x1 = (cx + dx) / dr * r;
    y1 = (cy + dy) / dr * r;

    float temp_x {(x1 + dx) / dr * Parameter::triangle_height};
    float temp_y {(y1 + dy) / dr * Parameter::triangle_height};

    x2 = (temp_x + dy) / dr * Parameter::triangle_height / Parameter::sqrt_3;
    y2 = (temp_y - dx) / dr * Parameter::triangle_height / Parameter::sqrt_3;

    x3 = (temp_x - dy) / dr * Parameter::triangle_height / Parameter::sqrt_3;
    y3 = (temp_y + dx) / dr * Parameter::triangle_height / Parameter::sqrt_3;
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
    color = al_map_rgba_f(1, 0, 1, 1);
}

void Aim::cyan()
{
    color = al_map_rgba_f(0, 1, 1, 1);
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
