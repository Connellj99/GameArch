/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "RightMouseEvent.h"

RightMouseEvent::RightMouseEvent(const Vector2D& loc)
	:Event(RIGHT_MOUSE_EVENT)
	, mLoc(loc)
{

}

RightMouseEvent::~RightMouseEvent()
{

}