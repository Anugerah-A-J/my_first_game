#include "Fence.h"
#include "Parameter.h"
#include <allegro5/allegro_primitives.h>

void Fence::draw() const
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
}

bool Fence::contain(Pawn* pawn)
{
    bool pawn_is_inside {
        pawn->get_cx() > x1 + Parameter::radius &&
        pawn->get_cx() < x2 - Parameter::radius &&
        pawn->get_cy() > y1 + Parameter::radius &&
        pawn->get_cy() < y2 - Parameter::radius
    };

    if (pawn_is_inside)
        return true;

    return false;
}

void Fence::resolve(Pawn* pawn)
{
    if (pawn->get_cx() < x1 + Parameter::radius && 
        pawn->get_cy() >= y1 + Parameter::radius &&
        pawn->get_cy() <= y2 - Parameter::radius) resolve_left(pawn);
        
    else if (pawn->get_cx() > x2 - Parameter::radius &&
        pawn->get_cy() >= y1 + Parameter::radius &&
        pawn->get_cy() <= y2 - Parameter::radius) resolve_right(pawn);
        
    else if (pawn->get_cy() < y1 + Parameter::radius &&
        pawn->get_cx() >= x1 + Parameter::radius &&
        pawn->get_cx() <= x2 - Parameter::radius) resolve_top(pawn);
        
    else if (pawn->get_cy() > y2 - Parameter::radius &&
        pawn->get_cx() >= x1 + Parameter::radius &&
        pawn->get_cx() <= x2 - Parameter::radius) resolve_bottom(pawn);
        
    else if (pawn->get_cx() < x1 + Parameter::radius && 
        pawn->get_cy() < y1 + Parameter::radius)
    {
        float tan {
            y1 + Parameter::radius - pawn->get_cy() /
            x1 + Parameter::radius - pawn->get_cx()
        };

        float tan_d {pawn->get_dy() / pawn->get_dx()};

        if (tan_d >= tan)
            resolve_left(pawn);
        else if (tan_d < tan)
            resolve_top(pawn);
    }

    else if (pawn->get_cx() > x2 - Parameter::radius && 
        pawn->get_cy() > y2 - Parameter::radius)
    {
        float tan {
            y2 - Parameter::radius - pawn->get_cy() /
            x2 - Parameter::radius - pawn->get_cx()
        };

        float tan_d {pawn->get_dy() / pawn->get_dx()};

        if (tan_d >= tan)
            resolve_right(pawn);
        else if (tan_d < tan)
            resolve_bottom(pawn);
    }

    else if (pawn->get_cx() < x1 + Parameter::radius && 
        pawn->get_cy() > y2 - Parameter::radius)
    {
        float tan {
            y2 - Parameter::radius - pawn->get_cy() /
            x1 + Parameter::radius - pawn->get_cx()
        };

        float tan_d {pawn->get_dy() / pawn->get_dx()};

        if (tan_d <= tan)
            resolve_left(pawn);
        else if (tan_d > tan)
            resolve_bottom(pawn);
    }

    else if (pawn->get_cx() > x2 - Parameter::radius && 
        pawn->get_cy() < y1 + Parameter::radius)
    {
        float tan {
            y1 + Parameter::radius - pawn->get_cy() /
            x2 - Parameter::radius - pawn->get_cx()
        };

        float tan_d {pawn->get_dy() / pawn->get_dx()};

        if (tan_d <= tan)
            resolve_right(pawn);
        else if (tan_d > tan)
            resolve_top(pawn);
    }
}

void Fence::resolve_left(Pawn* pawn)
{
    float dx {x1 + Parameter::radius - pawn->get_cx()};
    float dy {dx / pawn->get_dx() * pawn->get_dy()};

    pawn->move(dx, dy);
}

void Fence::resolve_right(Pawn* pawn)
{
    float dx {x2 - Parameter::radius - pawn->get_cx()};
    float dy {dx / pawn->get_dx() * pawn->get_dy()};

    pawn->move(dx, dy);
}

void Fence::resolve_top(Pawn* pawn)
{
    float dy {y1 + Parameter::radius - pawn->get_cy()};
    float dx {dy / pawn->get_dy() * pawn->get_dx()};

    pawn->move(dx, dy);
}

void Fence::resolve_bottom(Pawn* pawn)
{
    float dy {y2 - Parameter::radius - pawn->get_cy()};
    float dx {dy / pawn->get_dy() * pawn->get_dx()};

    pawn->move(dx, dy);
}