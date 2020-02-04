/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class DeleteEvent : public Event
{
private:
	int mXPos, mYPos;

public:
	// Constructor
	DeleteEvent(int x, int y) : Event((EventType)DELETE_EVENT),
		mXPos(x), mYPos(y) {}

	// Accessor
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	// Destructor
	~DeleteEvent() {}
};