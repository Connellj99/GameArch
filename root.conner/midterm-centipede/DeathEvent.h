/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class DeathEvent : public Event
{
private:

public:
	// Constructor
	DeathEvent() : Event((EventType)DEATH_EVENT) {}
};