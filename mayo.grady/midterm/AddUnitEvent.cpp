/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "AddUnitEvent.h"

AddUnitEvent::AddUnitEvent(const Vector2D& loc)
	:Event(EventType(ADD_UNIT_EVENT))
	, mLoc(loc)
{

}

AddUnitEvent::~AddUnitEvent()
{

}