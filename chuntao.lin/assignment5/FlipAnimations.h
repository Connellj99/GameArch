#ifndef FLIP_ANIMATIONS_H
#define FLIP_ANIMATIONS_H

#include "GameEvent.h"

//Toggle anim class for making animations stop and or resume
class FlipAnimEvent : public Event
{
public:

	// Constructors
	FlipAnimEvent() :Event((EventType)FLIP_ANIMATIONS) {};

	// Destructors
	~FlipAnimEvent() {};

private:
};

#endif

