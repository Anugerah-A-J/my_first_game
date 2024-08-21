#include "Parameter.h"
#include "Rectangle.h"
#include "Circle.h"
#ifndef BLACK_KING_H
#define BLACK_KING_H

#pragma once

class Black_king
{
public:
    Black_king();
    // ~Black_king();
    void draw() const;
private:
    Rectangle throne;
    Circle king;
};

#endif