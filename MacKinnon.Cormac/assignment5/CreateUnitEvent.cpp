#include "CreateUnitEvent.h"



CreateUnitEvent::CreateUnitEvent(Vector2D pos) 
	: Event(CREATE_UNIT_EVENT)
{
	mMousePos = pos;
}

CreateUnitEvent::~CreateUnitEvent()
{
}

Vector2D CreateUnitEvent::getMousePos() const
{
	return mMousePos;
}
