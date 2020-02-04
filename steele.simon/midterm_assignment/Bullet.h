#ifndef BULLET_H
#define BULLET_H

#include "Unit.h"

class Bullet : public Unit
{
public:

	// Friends
	friend class UnitManager;

	// Update Functions
	void update(double newTimeBetweenFrames);

private:

	// Constructors
	Bullet();
	Bullet(Vector2 newPos);

	// Destructors
	~Bullet();

};

#endif // !BULLET_H

