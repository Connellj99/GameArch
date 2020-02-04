#ifndef PLACEUNITEVENT_H
#define PLACEUNITEVENT_H

// Local includes
#include "GameEvent.h"

// Graphics-lib includes
#include <Vector2.h>


class PlaceUnitEvent : public Event
{
public:

	// Constructors
	PlaceUnitEvent(const Vector2& loc);

	// Accessors
	Vector2 getLocation() const { return mLoc; };

private:

	// Vector2's
	Vector2 mLoc;
};

#endif // !PLACEUNITEVENT_H

