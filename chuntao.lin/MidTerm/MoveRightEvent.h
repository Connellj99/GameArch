#ifndef MOVE_RIGHT_EVENT_H
#define MOVE_RIGHT_EVENT_H

#include "GameEvent.h"

//class that will let me quit the game
class MoveRightEvent : public Event
{
public:

	// Constructors
	MoveRightEvent() :Event((EventType)MOVE_RIGHT) {};

	// Destructors
	~MoveRightEvent() {};

private:
};

#endif

