#ifndef PAWN_H
#define PAWN_H

#pragma once

class Pawn
{
public:
    virtual void move(float dx, float dy) = 0;
private:
};

#endif