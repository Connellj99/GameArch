#ifndef GOOMBA_H
#define GOOMBA_H


// Local includes
#include "Unit.h"


enum GoombaDirection 
{
	LEFT,
	RIGHT
};


class Goomba : public Unit
{
public:

	// Constructors
	Goomba();
	Goomba(Vector2 newPos);

	// Destructors
	~Goomba();

	// Update functions
	void update(double newTimeBetweenFrames);

private:

	// Doubles
	double mVelocity;

	// Goomba Directions
	GoombaDirection mCurrentDirection;

};

#endif // !GOOMBA_H
