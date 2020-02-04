#include "CreateUnitEvent.h"

//constructor with paassed in vector coords
CreateUnit::CreateUnit(const Vector2& position)
	:Event(EventType(CREATE))
	, mPos(position)
{
}
