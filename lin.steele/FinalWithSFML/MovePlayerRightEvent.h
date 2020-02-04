#ifndef MOVEPLAYERRIGHTEVENT_H
#define MOVEPLAUERRIGHTEVENT_H

// Local Includes
#include "GameEvent.h"

class MovePlayerRightEvent : public Event
{
public:

	// Constructors
	MovePlayerRightEvent() :Event((EventType)MOVE_PLAYER_RIGHT) {};

	// Destructors
	~MovePlayerRightEvent() {};

private:

};


#endif // !MOVEPLAYERRIGHTEVENT_H

