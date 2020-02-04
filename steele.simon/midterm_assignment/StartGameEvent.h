#ifndef STARTGAMEEVENT_H
#define STARTGAMEEVENT_H

// Local Includes
#include "GameEvent.h"

class StartGameEvent: public Event
{
public:

	// Constructors
	StartGameEvent() :Event((EventType)START_GAME) {};

	// Destructors
	~StartGameEvent() {};

private:

};

#endif // !STARTGAMEEVENT_H

