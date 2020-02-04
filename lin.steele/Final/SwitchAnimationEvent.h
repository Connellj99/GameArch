#ifndef SWITCHANIMATIONEVENT_H
#define SWITCHANIMATIONEVENT_H

// Local includes
#include "GameEvent.h"


class SwitchAnimationEvent : public Event
{
public:

	// Constructors
	SwitchAnimationEvent() :Event((EventType)SWITCH_ANIMATIONS) {};
	
	// Destructors
	~SwitchAnimationEvent() {};

private:
};

#endif // !SWITCHANIMATIONEVENT_H

