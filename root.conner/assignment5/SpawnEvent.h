/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class SpawnEvent : public Event
{
private:
	int mXPos, mYPos;

public:
	// Constructor
	SpawnEvent(int x, int y) : Event((EventType)SPAWN_EVENT),
		mXPos(x), mYPos(y) {}

	// Accessor
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	// Destructor
	~SpawnEvent() {}
};