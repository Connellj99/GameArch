#ifndef EXIT_H
#define EXIT_H

#include "GameEvent.h"

//class that will let me quit the game
class ExitEvent : public Event
{
public:

	// Constructors
	ExitEvent() :Event((EventType)EXIT) {};

	// Destructors
	~ExitEvent() {};

private:
};

#endif

