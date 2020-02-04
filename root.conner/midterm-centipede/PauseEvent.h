/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class PauseEvent : public Event
{
private:

public:
	// Constructor
	PauseEvent() : Event((EventType)PAUSE_ANIM_EVENT) {}

	// Destructor
	~PauseEvent() {}
};