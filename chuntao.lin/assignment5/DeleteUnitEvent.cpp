#include "DeleteUnitEvent.h"

//constructor with paassed in vector coords
DeleteUnit::DeleteUnit(const Vector2& position)
	:Event(EventType(KILL))
	, mPos(position)
{
}
