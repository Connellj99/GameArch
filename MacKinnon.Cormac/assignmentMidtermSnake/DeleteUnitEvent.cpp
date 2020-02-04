#include "DeleteUnitEvent.h"



DeleteUnitEvent::DeleteUnitEvent(Vector2D pos) 
	: Event((EventType)GameEvents::DESTROY_UNIT_EVENT)
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
