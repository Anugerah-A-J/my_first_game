#ifndef WHITE_KING_H
#define WHITE_KING_H
#pragma once

#include "Parameter.h"
#include "Rectangle.h"
#include "Filled_circle.h"

class White_king
{
public:
    White_king();
    // ~White_king();
    void draw() const;
private:
    Rectangle throne;
    Filled_circle king;
};

#endif