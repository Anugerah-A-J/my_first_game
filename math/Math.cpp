#include "math.h"
#include <cmath>

bool equal(float f1, float f2, float delta)
{
    return fabsf(f1 - f2) < delta;
}