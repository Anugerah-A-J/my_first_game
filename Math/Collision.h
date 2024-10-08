#include "../Shape/Circle.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Line.h"
#include "../Game_objects/Pawn.h"
#include "../Game_objects/Fence.h"
#include <vector>
#include <set>
#pragma once

class Collision
{
public:
    void operator()(std::set<Pawn*>& dying_pawns ,Pawn& pawn, const Fence& f);
    void operator()(std::set<Pawn*>& dying_pawns ,const Pawn& moving_pawn, std::vector<Pawn>& pawns);
private:
    float circle_vs_circle(const Circle& moving_circle, const Circle& nonmoving_circle, const Line& velocity);
    float circle_vs_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    float circle_inside_rectangle(const Circle& moving_circle, const Rectangle& nonmoving_rectangle, const Line& velocity);
    float intersect(const Line& line1, const Line& line2);
    float intersect(const Line& line, const Circle& circle);
};