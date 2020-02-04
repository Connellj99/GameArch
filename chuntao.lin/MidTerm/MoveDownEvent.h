#ifndef MOVE_DOWN_EVENT_H
#define MOVE_DOWn_EVENT_H

#include "GameEvent.h"

//class that will let me quit the game
class MoveDownEvent : public Event
{
public:

	// Constructors
	MoveDownEvent() :Event((EventType)MOVE_DOWN) {};

	// Destructors
	~MoveDownEvent() {};

private:
};

#endif

