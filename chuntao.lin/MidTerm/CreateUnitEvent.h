#ifndef CREATE_UNIT_H
#define CREATE_UNIT_H

#include "GameEvent.h"

#include <Vector2Data.h>

//clasds that will allow me to create unit at location
class CreateUnit : public Event
{
public:

	// Constructors
	CreateUnit(const Vector2& position);

	// Accessors
	Vector2 getLocation() const { return mPos; };

private:

	// Vector2's
	Vector2 mPos;
};

#endif

