#ifndef DESTROYUNITEVENT_H
#define DESTROYUNITEVENT_H

// Local Includes
#include "GameEvent.h"

// Graphics-Lib includes
#include <Vector2.h>


class DestroyUnitEvent : public Event
{
public:

	// Constructors
	DestroyUnitEvent(const Vector2& loc);

	// Accessors
	Vector2 getLocation() const { return mLoc; };

private:

	// Vector2's
	Vector2 mLoc;
};

#endif // !DESTROYUNITEVENT_H

