/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "RemoveUnitEvent.h"

RemoveUnitEvent::RemoveUnitEvent(const Vector2D& loc)
	:Event(EventType(REMOVE_UNIT_EVENT))
	, mLoc(loc)
{

}

RemoveUnitEvent::~RemoveUnitEvent()
{

}