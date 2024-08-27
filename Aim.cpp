#include "Aim.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Aim::Aim():
    cx{0},
    cy{0},
    r{Parameter::reach_radius},
    color{al_map_rgba_f(1, 1, 1, 1)},
    thickness{Parameter::line_width},
    x{cx},
    y{cy},
    xs{},
    ys{}
{
}

void Aim::draw() const
{
    al_draw_circle(cx, cy, r, color, thickness);
    al_draw_line(cx, cy, x, y, color, thickness);
}

void Aim::set_center(float cx, float cy)
{
    this->cx = cx;
    this->cy = cy;
    this->x = cx;
    this->y = cy;

    xs.at(0) = cx;
    ys.at(0) = cy - r;

    xs.at(1) = cx + r / 2;
    ys.at(1) = cy - r / 2 * Parameter::sqrt_3;
    
    xs.at(2) = cx + r / 2 * Parameter::sqrt_3;
    ys.at(2) = cy - r / 2;

    xs.at(3) = cx + r;
    ys.at(3) = cy;

    xs.at(4) = xs.at(2);
    ys.at(4) = cy + r / 2;

    xs.at(5) = xs.at(1);
    ys.at(5) = cy + r / 2 * Parameter::sqrt_3;

    xs.at(6) = xs.at(0);
    ys.at(6) = cy + r;

    xs.at(7) = cx - r / 2;
    ys.at(7) = ys.at(5);

    xs.at(8) = cx - r / 2 * Parameter::sqrt_3;
    ys.at(8) = ys.at(4);

    xs.at(9) = cx - r;
    ys.at(9) = ys.at(3);

    xs.at(10) = xs.at(8);
    ys.at(10) = ys.at(2);

    xs.at(11) = xs.at(7);
    ys.at(11) = ys.at(1);
}

void Aim::update_xy(float mouse_x, float mouse_y)
{
    float delta_x {mouse_x - cx};
    float delta_y {cy - mouse_y};
    float sin {delta_y / sqrtf(delta_x * delta_x + delta_y * delta_y)};

    if (sin <= 1 && sin >= Parameter::sin_75)
    {
        x = xs.at(0);
        y = ys.at(0);
    }
    else if (sin <= Parameter::sin_75 && sin >= Parameter::sin_45)
    {
        x = delta_x > 0 ? xs.at(1) : xs.at(11);
        y = delta_x > 0 ? ys.at(1) : ys.at(11);
    }
    else if (sin <= Parameter::sin_45 && sin >= Parameter::sin_15)
    {
        x = delta_x > 0 ? xs.at(2) : xs.at(10);
        y = delta_x > 0 ? ys.at(2) : ys.at(10);
    }
    else if (sin <= Parameter::sin_15 && sin >= -Parameter::sin_15)
    {
        x = delta_x > 0 ? xs.at(3) : xs.at(9);
        y = delta_x > 0 ? ys.at(3) : ys.at(9);
    }
    else if (sin <= -Parameter::sin_15 && sin >= -Parameter::sin_45)
    {
        x = delta_x > 0 ? xs.at(4) : xs.at(8);
        y = delta_x > 0 ? ys.at(4) : ys.at(8);
    }
    else if (sin <= -Parameter::sin_45 && sin >= -Parameter::sin_75)
    {
        x = delta_x > 0 ? xs.at(5) : xs.at(7);
        y = delta_x > 0 ? ys.at(5) : ys.at(7);
    }
    else if (sin <= -Parameter::sin_75 && sin >= -1)
    {
        x = xs.at(6);
        y = ys.at(6);
    }
}

// void Aim::hide()
// {
//     color = Parameter::window_color();
// }

// void Aim::show()
// {
//     color = al_map_rgba_f(1, 1, 1, 1);
// }

float Aim::get_x() const
{
    return x;
}

float Aim::get_y() const
{
    return y;
}