/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "EventTypes.h"

#include "Event.h"
#include "UnitEvents.h"

// Create a new create unit event.
CreateUnitEvent::CreateUnitEvent(int _positionX, int _positionY):
	Event(EventType(CREATE_UNIT))
{
	mPositionX = _positionX;
	mPositionY = _positionY;

	return;
}

// Get the position.
void CreateUnitEvent::getPosition(int & _x, int & _y)
{
	_x = mPositionX;
	_y = mPositionY;

	return;
}

// Remove a unit event.
RemoveUnitEvent::RemoveUnitEvent(int _positionX, int _positionY):
	Event(EventType(REMOVE_UNIT))
{
	mPositionX = _positionX;
	mPositionY = _positionY;

	return;
}

// Get the position.
void RemoveUnitEvent::getPosition(int & _x, int & _y)
{
	_x = mPositionX;
	_y = mPositionY;

	return;
}
