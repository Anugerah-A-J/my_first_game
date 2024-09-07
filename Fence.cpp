#include "Fence.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

Fence::Fence(Pawn_mover* pm):
    x1{2 * Parameter::space},
    y1{Parameter::space},
    x2{Parameter::window_width - 2 * Parameter::space},
    y2{Parameter::window_height - Parameter::space},
    color{al_map_rgb_f(1, 0, 0)},
    thickness{Parameter::line_width},
    pm{pm}
{
}

void Fence::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
}

void Fence::check()
{
    if (pm->get_pawn() == nullptr)
        return;
        
    bool pawn_is_inside {
        pm->get_pawn()->get_cx() > x1 + Parameter::radius &&
        pm->get_pawn()->get_cx() < x2 - Parameter::radius &&
        pm->get_pawn()->get_cy() > y1 + Parameter::radius &&
        pm->get_pawn()->get_cy() < y2 - Parameter::radius
    };

    if (pawn_is_inside)
        return;

    pm->finish();
    resolve();
    pm->kill_pawn();
}

void Fence::resolve()
{
    if (pm->get_pawn()->get_cx() < x1 + Parameter::radius && 
        pm->get_pawn()->get_cy() >= y1 + Parameter::radius &&
        pm->get_pawn()->get_cy() <= y2 - Parameter::radius) resolve_left();
        
    else if (pm->get_pawn()->get_cx() > x2 - Parameter::radius &&
        pm->get_pawn()->get_cy() >= y1 + Parameter::radius &&
        pm->get_pawn()->get_cy() <= y2 - Parameter::radius) resolve_right();
        
    else if (pm->get_pawn()->get_cy() < y1 + Parameter::radius &&
        pm->get_pawn()->get_cx() >= x1 + Parameter::radius &&
        pm->get_pawn()->get_cx() <= x2 - Parameter::radius) resolve_top();
        
    else if (pm->get_pawn()->get_cy() > y2 - Parameter::radius &&
        pm->get_pawn()->get_cx() >= x1 + Parameter::radius &&
        pm->get_pawn()->get_cx() <= x2 - Parameter::radius) resolve_bottom();
        
    else if (pm->get_pawn()->get_cx() < x1 + Parameter::radius && 
        pm->get_pawn()->get_cy() < y1 + Parameter::radius)
    {
        float tan {
            y1 + Parameter::radius - pm->get_pawn()->get_cy() /
            x1 + Parameter::radius - pm->get_pawn()->get_cx()
        };

        float tan_d {pm->get_dy() / pm->get_dx()};

        if (tan_d >= tan)
            resolve_left();
        else if (tan_d < tan)
            resolve_top();
    }

    else if (pm->get_pawn()->get_cx() > x2 - Parameter::radius && 
        pm->get_pawn()->get_cy() > y2 - Parameter::radius)
    {
        float tan {
            y2 - Parameter::radius - pm->get_pawn()->get_cy() /
            x2 - Parameter::radius - pm->get_pawn()->get_cx()
        };

        float tan_d {pm->get_dy() / pm->get_dx()};

        if (tan_d >= tan)
            resolve_right();
        else if (tan_d < tan)
            resolve_bottom();
    }

    else if (pm->get_pawn()->get_cx() < x1 + Parameter::radius && 
        pm->get_pawn()->get_cy() > y2 - Parameter::radius)
    {
        float tan {
            y2 - Parameter::radius - pm->get_pawn()->get_cy() /
            x1 + Parameter::radius - pm->get_pawn()->get_cx()
        };

        float tan_d {pm->get_dy() / pm->get_dx()};

        if (tan_d <= tan)
            resolve_left();
        else if (tan_d > tan)
            resolve_bottom();
    }

    else if (pm->get_pawn()->get_cx() > x2 - Parameter::radius && 
        pm->get_pawn()->get_cy() < y1 + Parameter::radius)
    {
        float tan {
            y1 + Parameter::radius - pm->get_pawn()->get_cy() /
            x2 - Parameter::radius - pm->get_pawn()->get_cx()
        };

        float tan_d {pm->get_dy() / pm->get_dx()};

        if (tan_d <= tan)
            resolve_right();
        else if (tan_d > tan)
            resolve_top();
    }
}

void Fence::resolve_left()
{
    float dx {x1 + Parameter::radius - pm->get_pawn()->get_cx()};
    float dy {dx / pm->get_dx() * pm->get_dy()};

    pm->get_pawn()->move(dx, dy);
}

void Fence::resolve_right()
{
    float dx {x2 - Parameter::radius - pm->get_pawn()->get_cx()};
    float dy {dx / pm->get_dx() * pm->get_dy()};

    pm->get_pawn()->move(dx, dy);
}

void Fence::resolve_top()
{
    float dy {y1 + Parameter::radius - pm->get_pawn()->get_cy()};
    float dx {dy / pm->get_dy() * pm->get_dx()};

    pm->get_pawn()->move(dx, dy);
}

void Fence::resolve_bottom()
{
    float dy {y2 - Parameter::radius - pm->get_pawn()->get_cy()};
    float dx {dy / pm->get_dy() * pm->get_dx()};

    pm->get_pawn()->move(dx, dy);
}