/*
 * Pawn.h
 *
 *  Created on: 31 Aug 2024
 *      Author: HP
 */

#ifndef PAWN_H_
#define PAWN_H_

class Pawn {
public:
	virtual float get_cx() const = 0;
	virtual float get_cy() const = 0;
	virtual void move(float dx, float dy) = 0;
	virtual bool is_dead() = 0;
    virtual void dying() = 0;
};

#endif /* PAWN_H_ */
