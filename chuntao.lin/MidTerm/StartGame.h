#ifndef START_GAME_H
#define START_GAME_H

#include "GameEvent.h"

//class that will let me quit the game
class StartEvent : public Event
{
public:

	// Constructors
	StartEvent() :Event((EventType)START) {};

	// Destructors
	~StartEvent() {};

private:
};

#endif

