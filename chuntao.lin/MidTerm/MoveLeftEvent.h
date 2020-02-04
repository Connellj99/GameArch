#ifndef MOVE_LEFT_EVENT_H
#define MOVE_LEFT_EVENT_H

#include "GameEvent.h"

//class that will let me quit the game
class MoveLeftEvent : public Event
{
public:

	// Constructors
	MoveLeftEvent() :Event((EventType)MOVE_LEFT) {};

	// Destructors
	~MoveLeftEvent() {};

private:
};

#endif

