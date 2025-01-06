#include "Shape.hpp"
#pragma once

class Translation
{
public:
    explicit Translation(Vector& start_position);
    void Reset_all(const Vector& end);
    bool Finish() const;
    bool Just_finish() const;
    void Move(Circle& circle);
    void Reflected_by(const Vector &normal_unit);
    Line Latest() const;
    void Stop();
private:
    unsigned int step_count;
    Vector ideal_displacement; // without considering collision resolving
    Vector& current_position;
    Vector previous_position;
};

class Collision
{
public:
    bool Earlier_than(const Collision& collision) const;
    virtual void Reflect() = 0;
    // virtual void Stop() = 0;
    // virtual void Slide() = 0;
protected:
    float t;
    static void Intersect(const Line& line1, float& t1, const Line& line2, float& t2);
    static float Intersect(const Circle& circle1, const Translation& translation1, const Circle& circle2, const Translation& translation2);
    static float Intersect(const Circle& moving_circle, const Translation& translation, Circle& nonmoving_circle);
};

class Circle_inside_rectangle : public Collision
{
public:
    Circle_inside_rectangle(Circle& moving_circle, Translation& circle_translation, const Rectangle& nonmoving_rectangle);
private:
    void Reflect() override;
    Vector normal_unit;
    Circle& circle;
    Translation& circle_translation;
    Rectangle& rectangle;
};

class Circle_outside_circle : public Collision
{
public:
    Circle_outside_circle(Circle& circle_1, Translation& translation_1, Circle& circle_2, Translation& translation_2);
private:
    void Reflect() override;
    Vector normal_unit;
    Circle& circle_1;
    Circle& circle_2;
};

class Circle_outside_rectangle : public Collision
{
public:
    Circle_outside_rectangle(Circle& moving_circle, Translation& circle_translation, const Rectangle& nonmoving_rectangle);
private:
    void Reflect() override;
    Vector normal_unit;
    Circle& circle;
    Translation& circle_translation;
    Rectangle& rectangle;
};
