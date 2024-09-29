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
	// void move(float dx, float dy);
    void stop();
    // float get_dx() const;
	// float get_dy() const;

private:
    inline static unsigned int move_step_count = 0;
    inline static Vector d = Vector(0, 0);
    Circle circle_shape;
    ALLEGRO_COLOR color;
};