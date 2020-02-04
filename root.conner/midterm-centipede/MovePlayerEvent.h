/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class MovePlayerEvent : public Event
{
private:
	int mXPos, mYPos;

public:
	// Constructor
	MovePlayerEvent(int x, int y) : Event((EventType)MOVE_PLAYER_EVENT),
		mXPos(x), mYPos(y) {}

	// Accessor
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	// Destructor
	~MovePlayerEvent() {}
};