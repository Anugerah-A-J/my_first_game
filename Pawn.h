#include "Parameter.h"
#ifndef PAWN_H
#define PAWN_H
#pragma once

class Pawn
{
public:
    Pawn(float cx, float cy, float red, float green, float blue);
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const;
    float get_cy() const;

    void move();
	void move(float dx, float dy);
    void update_dxdy(float x_finish, float y_finish);
    void stop();
    float get_dx() const;
	float get_dy() const;

    bool is_dead();
    void die();
private:
    inline static unsigned int move_step_count {0};
	inline static float dx                     {0};
	inline static float dy                     {0};
    float cx, cy, r {Parameter::radius};
    float red, green, blue;
};

#endif