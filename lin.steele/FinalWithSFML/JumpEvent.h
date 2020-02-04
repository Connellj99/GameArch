#ifndef JUMPEVENT_H
#define JUMPEVENT_H

// Local Includes
#include "GameEvent.h"

class JumpEvent: public Event
{
public:

	// Constructors
	JumpEvent() :Event((EventType)MAKE_PLAYER_JUMP) {};

	// Destructors
	~JumpEvent() {};

private:

};

#endif // !STARTGAMEEVENT_H

