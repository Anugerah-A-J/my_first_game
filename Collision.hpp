#include <set>
#include "Pawn.hpp"
#include "Fence.hpp"
#include <vector>
#include "King.hpp"
#include "Aim.hpp"
#pragma once

class Collision
{
public:
    static void response(std::set<Pawn*>& dying_pawns ,Pawn& moving_pawn, const Fence& fence)
    {
        float t = circle_inside_rectangle(moving_pawn.shape, fence.shape, moving_pawn.move_step_line_segment());

        if (t == 2 || Pawn::dead_without_dying)
            return;
        
        moving_pawn.retreat(1 - t);
        moving_pawn.stop();
        dying_pawns.emplace(&moving_pawn);
    };

    static void response(std::set<Pawn*>& dying_pawns ,const Pawn& moving_pawn, std::vector<Pawn>& pawns)
    {
        for (auto& pawn: pawns)
        {
            if (circle_vs_circle(moving_pawn.shape, pawn.shape, moving_pawn.move_step_line_segment()) == 2)
                continue;

            dying_pawns.emplace(&pawn);
        }
    };

    static void response(Pawn& moving_pawn, King& king, bool friendly_fire, const Aim& aim)
    {
        float t = circle_vs_rectangle(moving_pawn.shape, king.shape_rectangle, moving_pawn.move_step_line_segment());

        if (t == 2 || Pawn::dead_without_dying)
            return;

        if (friendly_fire && !king.contain(aim.shape_circle.center))
        {
            moving_pawn.retreat(1 - t);
            moving_pawn.stop();
        }
        else if (!friendly_fire)
            Pawn::dead_without_dying = true;
    };
private:
    static float circle_vs_circle(const Circle& moving_circle, const Circle& nonmoving_circle, const Line& velocity);
    static float circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    static float circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    static float intersect(const Line& line1, const Line& line2);
    static float intersect(const Line& line, const Circle& circle);
};