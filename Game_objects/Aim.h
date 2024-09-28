#include <allegro5/color.h>
#include "Parameter.h"
#include "../Shape/Circle.h"
#include "../Shape/Triangle.h"
#pragma once

class Aim
{
public:
    void draw() const;
    void set_center(int x, int y);
    void rotate(float x, float y);

    const Vector& get_center() const;
    const Vector& get_end_point() const;
    
    void magenta();
    void cyan();

    void show();
    void hide();
    bool get_visible() const;
private:
    Circle circle_shape = Circle(0, 0, Parameter::reach_radius());

    Vector end_point = Vector(0, 0);
    
    Triangle triangle_shape = Triangle(Vector(0, 0), Vector(0, 0), Vector(0, 0));
    
    ALLEGRO_COLOR color = Parameter::magenta();
    
    float thickness = Parameter::line_width();
    
    bool visible = false;
};