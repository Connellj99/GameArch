#include "PlaceUnitEvent.h"

// This is the default constructor for the class
PlaceUnitEvent::PlaceUnitEvent(const Vector2& loc)
	:Event(EventType(CREATE_UNITS))
	, mLoc(loc)
{
}