#include "../Math/Vector.h"
#include "../Parameter.h"
#include "../Shape/Line.h"
#include "../Shape/Circle.h"
#pragma once

class Pawn
{
public:
    Pawn(float cx, float cy, ALLEGRO_COLOR color);

    void draw() const;
    bool pointed_by(const Vector& v) const;
    const Vector& get_center() const;
    static bool finish_moving();
    const Circle& get_shape() const;
    const Line get_velocity() const;

    static void update_d(const Vector& start, const Vector& end);
    static void reset_move_step_count();

    void move();
    void retreat(float f);
    void stop();
    void die();
    bool is_dead();
    static bool is_dead_immediately_after_finish_moving();
    static void set_dead_immediately_after_finish_moving(bool b);

private:
    inline static unsigned int move_step_count = Parameter::move_step();
    inline static Vector d = Vector(0, 0);
    inline static bool dead_immediately_after_finish_moving = false;
    Circle circle_shape;
    ALLEGRO_COLOR color;
};