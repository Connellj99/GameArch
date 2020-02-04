#ifndef PLAYER_H
#define PLAYER_H

// Local includes
#include "Unit.h"

enum Direction
{
	MOVING_LEFT,
	MOVING_RIGHT
};


class Player : public Unit
{
public:

	// Friends
	friend class UnitManager;

	// Update functions
	void update(double newTimeBetweenFrames);

	// Mutators
	void jump();
	void movePlayerRight();
	void movePlayerLeft();

private:

	// Constructors
	Player();
	Player(Vector2 newPos);

	// Destructors
	~Player();

	// Numbers
	double mVelocity;
	double mMaxJumpForce;

	// Booleans
	bool mIsJumping;
	bool mInMidAir;
	bool mBounce;
	bool mIsMoving;

	// Directions
	Direction mCurrentDirection;
};


#endif // !PLAYER_H

