#ifndef DELETE_UNIT_H
#define DELETE_UNIT_H

#include "GameEvent.h"

#include <Vector2Data.h>

//class that will allow me to delete units
class DeleteUnit : public Event
{
public:

	// Constructors
	DeleteUnit(const Vector2& position);

	// Accessors
	Vector2 getLocation() const { return mPos; };

private:

	// Vector2's
	Vector2 mPos;
};

#endif

