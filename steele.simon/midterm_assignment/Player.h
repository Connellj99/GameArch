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

private:

	// Constructors
	Player();
	Player(Vector2 newPos);

	// Destructors
	~Player();

};


#endif // !PLAYER_H

