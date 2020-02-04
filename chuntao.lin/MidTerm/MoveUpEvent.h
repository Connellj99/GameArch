#ifndef MOVE_UP_EVENT_H
#define MOVE_UP_EVENT_H

#include "GameEvent.h"

//class that will let me quit the game
class MoveUpEvent : public Event
{
public:

	// Constructors
	MoveUpEvent() :Event((EventType)MOVE_UP) {};

	// Destructors
	~MoveUpEvent() {};

private:
};

#endif

