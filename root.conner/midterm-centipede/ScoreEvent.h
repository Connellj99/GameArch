/*
Conner Root
EGP 310-01
*/

#pragma once

#include "Event.h"
#include "GameEvent.h"

class ScoreEvent : public Event
{
private:
	char mFlag;

public:
	// Constructor
	ScoreEvent(char f) : Event((EventType)SCORE_EVENT), mFlag(f) {}

	// Accessor 
	char getFlag() { return mFlag; }

	// Destructor
	~ScoreEvent() {}
};