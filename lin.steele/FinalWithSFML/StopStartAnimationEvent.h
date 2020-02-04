#ifndef STOPSTARTANIMATIONEVENT_H
#define STOPSTARTANIMATIONEVENT_H

// Local includes
#include "GameEvent.h"


class StopStartAnimationEvent : public Event
{
public:

	// Constructors
	StopStartAnimationEvent() :Event((EventType)STOP_START_ANIMATION) {};

	// Destructors
	~StopStartAnimationEvent() {};

private:
};

#endif // !STOPSTARTANIMATIONEVENT_H

