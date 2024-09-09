#include "Parameter.h"
#ifndef PAWN_H_
#define PAWN_H_

class Pawn {
public:
	virtual float get_cx() const = 0;
	virtual float get_cy() const = 0;
	virtual float get_dx() const = 0;
	virtual float get_dy() const = 0;

	virtual void move() = 0;
	virtual void move(float dx, float dy) = 0;
	static unsigned int get_move_step_count() {return move_step_count;};
	virtual void update_dxdy(float x_finish, float y_finish) = 0;
	virtual void stop() = 0;
	
	virtual bool is_dead() = 0;
    virtual void dying() = 0;
	virtual void trigger_dying() = 0;
protected:
	// static unsigned int move_step_count;
    // static float dx;
    // static float dy;
	inline static unsigned int move_step_count {Parameter::move_step};
	inline static float dx {0};
	inline static float dy {0};
};

#endif