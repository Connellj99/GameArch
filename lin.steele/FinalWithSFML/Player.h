#ifndef PLAYER_H
#define PLAYER_H

// Local includes
#include "Unit.h"

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

	// Integers
	double mVelocity;

	// Booleans
	bool mIsJumping;
};


#endif // !PLAYER_H

