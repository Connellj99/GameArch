/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class ExitEvent : public Event
{
private:

public:
	// Constructor
	ExitEvent() : Event((EventType)EXIT_EVENT) {}

	// Destructor
	~ExitEvent() {}
};