#ifndef MUSHROOM_H
#define MUSHROOM_H

// Local Project includes
#include "Unit.h"

class Mushroom : public Unit
{
public:

	// Friends
	friend class UnitManager;

	// Update functions
	void update(double newTimeBetweenFrames);

private:

	// Constructors
	Mushroom();
	Mushroom(Vector2 newPos);

	// Destructors
	~Mushroom();

	// Integers
	int mHealth;

};

#endif // !MUSHROOM_H

