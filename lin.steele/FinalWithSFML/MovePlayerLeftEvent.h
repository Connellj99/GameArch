#ifndef MOVEPLAYERLEFTEVENT_H
#define MOVEPLAUERLEFTEVENT_H

// Local Includes
#include "GameEvent.h"

class MovePlayerLeftEvent : public Event
{
public:

	// Constructors
	MovePlayerLeftEvent() :Event((EventType)MOVE_PLAYER_LEFT) {};

	// Destructors
	~MovePlayerLeftEvent() {};

private:

};


#endif // !MOVEPLAYERLEFTEVENT_H

