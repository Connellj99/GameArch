/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class ToggleAnimationEvent : public Event
{
private:

public:
	// Constructor
	ToggleAnimationEvent() : Event((EventType)TOGGLE_ANIM_EVENT) {}

	// Destructor
	~ToggleAnimationEvent() {}
};