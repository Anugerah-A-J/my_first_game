#include "Pawn.h"
#include "Parameter.h"
#ifndef MAGENTA_PAWN_H
#define MAGENTA_PAWN_H
#pragma once

class Magenta_pawn:
     public Pawn
{
public:
    Magenta_pawn(float cx, float cy);
    void draw() const;
    bool pointed_by(int x, int y) const;
    float get_cx() const override;
    float get_cy() const override;

    void move() override;
	void move(float dx, float dy) override;
    void update_dxdy(float x_finish, float y_finish) override;
    void stop() override;
    float get_dx() const override;
	float get_dy() const override;

    bool is_dead() override;
    void dying() override;
    void trigger_dying() override;
private:
    float cx, cy;
    float r       {Parameter::radius};
    float red     {1};
    float green   {0};
    float blue    {1};
    bool is_dying {false};
};

#endif