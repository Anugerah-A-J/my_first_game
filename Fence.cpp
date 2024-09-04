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
    if (
        pm->get_pawn()->get_cx() < x1 + Parameter::radius && 
        pm->get_pawn()->get_cy() >= y1 + Parameter::radius &&
        pm->get_pawn()->get_cy() <= y2 - Parameter::radius
    )
    {
        float dx {x1 + Parameter::radius - pm->get_pawn()->get_cx()};
        float dy {dx / pm->get_dx() * pm->get_dy()};

        pm->get_pawn()->move(dx, dy);
    }
    else if (
        pm->get_pawn()->get_cx() > x2 - Parameter::radius &&
        pm->get_pawn()->get_cy() >= y1 + Parameter::radius &&
        pm->get_pawn()->get_cy() <= y2 - Parameter::radius
    )
    {
        float dx {x2 - Parameter::radius - pm->get_pawn()->get_cx()};
        float dy {dx / pm->get_dx() * pm->get_dy()};

        pm->get_pawn()->move(dx, dy);
    }
    else if (
        pm->get_pawn()->get_cy() < y1 + Parameter::radius &&
        pm->get_pawn()->get_cx() >= x1 + Parameter::radius &&
        pm->get_pawn()->get_cx() <= x2 - Parameter::radius
    )
    {
        float dy {y1 + Parameter::radius - pm->get_pawn()->get_cy()};
        float dx {dy / pm->get_dy() * pm->get_dx()};

        pm->get_pawn()->move(dx, dy);
    }
    else if (
        pm->get_pawn()->get_cy() > y2 - Parameter::radius &&
        pm->get_pawn()->get_cx() >= x1 + Parameter::radius &&
        pm->get_pawn()->get_cx() <= x2 - Parameter::radius
    )
    {
        float dy {y2 - Parameter::radius - pm->get_pawn()->get_cy()};
        float dx {dy / pm->get_dy() * pm->get_dx()};

        pm->get_pawn()->move(dx, dy);
    }
}