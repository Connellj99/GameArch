#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "Vector2D.h"

class RightMouseEvent : public Event
{
private:
	Vector2D mLoc;

public:
	RightMouseEvent( const Vector2D& loc );
	~RightMouseEvent();

	Vector2D getLocation() const { return mLoc; };
};