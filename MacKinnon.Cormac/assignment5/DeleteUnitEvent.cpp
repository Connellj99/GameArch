#include "DeleteUnitEvent.h"



DeleteUnitEvent::DeleteUnitEvent(Vector2D pos) 
	: Event(DESTROY_UNIT_EVENT)
{
	mMousePos = pos;
}

DeleteUnitEvent::~DeleteUnitEvent()
{
}

Vector2D DeleteUnitEvent::getMousePos() const
{
	return mMousePos;
}
