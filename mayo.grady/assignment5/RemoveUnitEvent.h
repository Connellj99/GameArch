#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"
#include "Vector2D.h"

class RemoveUnitEvent : public Event
{
private:
	Vector2D mLoc;

public:
	RemoveUnitEvent(const Vector2D& loc);
	~RemoveUnitEvent();

	Vector2D getLocation() const { return mLoc; };
};