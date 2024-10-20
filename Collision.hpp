#include <set>
#include "Pawn.hpp"
#include "Fence.hpp"
#include <vector>
#include "King.hpp"
#pragma once

class Collision
{
public:
    static void response(std::set<Pawn*>& dying_pawns ,Pawn& moving_pawn, const Fence& fence)
    {
        float t = circle_inside_rectangle(moving_pawn.shape, fence.shape, moving_pawn.move_step_line_segment());

        // std::cout << "t fence: " << t << "\n";
        // std::cout << "is dead immediately after finish moving: " << Pawn::is_dead_immediately_after_finish_moving() << "\n\n";

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

    static void response(Pawn& moving_pawn, King& king)
    {
        float t = circle_vs_rectangle(moving_pawn.shape, king.shape_rectangle, moving_pawn.move_step_line_segment());

        // std::cout << "t king: " << t << "\n\n";

        if (t == 2 || Pawn::dead_without_dying)
            return;

        // moving_pawn.stop();
        Pawn::dead_without_dying = true;
    };
private:
    static float circle_vs_circle(const Circle& moving_circle, const Circle& nonmoving_circle, const Line& velocity);
    static float circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    static float circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    static float intersect(const Line& line1, const Line& line2);
    static float intersect(const Line& line, const Circle& circle);
};