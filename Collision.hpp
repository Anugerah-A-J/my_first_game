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
    void Respond_to_reflection();
    Line Latest() const;
    void Stop();
    void Update_t(Circle& circle, float t);
    void Update_normal_unit(const Vector& normal_unit);
    void Update_t_and_normal_unit(Circle& circle, float t, const Vector& point);
private:
    float t;
    Vector normal_unit;
    unsigned int step_count;
    Vector ideal_displacement; // without considering collision resolving
    Vector& current_position;
    Vector previous_position;
};

class Collision
{
public:
    float Get_t() const;
    virtual void Update_translation_reflection() = 0;
    // virtual void Stop() = 0;
    // virtual void Slide() = 0;
protected:
    Collision();
    float t;
    Vector normal_unit;
    static void Intersect(const Line& line1, float& t1, const Line& line2, float& t2);
    static float Intersect(const Circle& circle1, const Translation& translation1, const Circle& circle2, const Translation& translation2);
    static float Intersect(const Circle& moving_circle, const Translation& translation, const Circle& nonmoving_circle);
    static float Intersect_circle_circle(const Vector& c, const Vector& v, float r);
};

class Circle_inside_rectangle : public Collision
{
public:
    Circle_inside_rectangle(Circle& moving_circle, Translation& circle_translation, const Rectangle& nonmoving_rectangle);
private:
    void Update_translation_reflection() override;
    Circle& moving_circle;
    Translation& circle_translation;
    const Rectangle& nonmoving_rectangle;
};

class Circle_outside_circle : public Collision
{
public:
    Circle_outside_circle(Circle& circle_1, Translation& translation_1, Circle& circle_2, Translation& translation_2);
private:
    void Update_translation_reflection() override;
    Circle& circle_1;
    Translation& translation_1;
    Circle& circle_2;
    Translation& translation_2;
};

class Circle_outside_rectangle : public Collision
{
public:
    Circle_outside_rectangle(Circle& moving_circle, Translation& circle_translation, const Rectangle& nonmoving_rectangle);
private:
    void Update_translation_reflection() override;
    Circle& moving_circle;
    Translation& circle_translation;
    const Rectangle& nonmoving_rectangle;
};
