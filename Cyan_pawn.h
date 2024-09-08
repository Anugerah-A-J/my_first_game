#include "Pawn.h"
#include "Parameter.h"
#ifndef CYAN_PAWN_H
#define CYAN_PAWN_H

#pragma once

class Cyan_pawn:
     public Pawn
{
public:
    Cyan_pawn(float cx, float cy);
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const override;
    float get_cy() const override;

    void move() override;
	void move(float dx, float dy) override;
    unsigned int get_move_step_count() const override;
    void update_dxdy(float x_finish, float y_finish) override;
    void stop() override;
    float get_dx() const override;
	float get_dy() const override;
    
    bool is_dead() override;
    void dying() override;
private:
    float cx, cy;
    float r     {Parameter::radius};
    float red   {0};
    float green {1};
    float blue  {1};
};

#endif
