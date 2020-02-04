#include "DestroyUnitEvent.h"

// This is the default constructor for the class
DestroyUnitEvent::DestroyUnitEvent(const Vector2& loc)
	:Event(EventType(DELETE_UNITS))
	, mLoc(loc)
{
}