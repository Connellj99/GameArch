/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "LeftMouseEvent.h"

LeftMouseEvent::LeftMouseEvent( const Vector2D& loc )
	:Event(LEFT_MOUSE_EVENT)
	, mLoc(loc)
{

}

LeftMouseEvent::~LeftMouseEvent()
{

}