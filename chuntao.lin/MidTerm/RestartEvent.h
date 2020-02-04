#ifndef RESTART_GAME_H
#define RESTART_GAME_H

#include "GameEvent.h"

//class that will let me quit the game
class RestartEvent : public Event
{
public:

	// Constructors
	RestartEvent() :Event((EventType)RESTART) {};

	// Destructors
	~RestartEvent() {};

private:
};

#endif

