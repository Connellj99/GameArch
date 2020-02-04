/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class ChangeSpeedEvent : public Event
{
private:
	int mChange;

public:
	// Constructor
	ChangeSpeedEvent(int s) : Event((EventType)SPEED_CHANGE_EVENT),
		mChange(s) {}

	// Accessor
	int getChange() { return mChange; }

	// Destructor
	~ChangeSpeedEvent() {}
};