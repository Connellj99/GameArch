#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "Vector2D.h"

class LeftMouseEvent : public Event
{
private:
	Vector2D mLoc;

public:
	LeftMouseEvent( const Vector2D& loc );
	~LeftMouseEvent();

	Vector2D getLocation() const { return mLoc; };
};