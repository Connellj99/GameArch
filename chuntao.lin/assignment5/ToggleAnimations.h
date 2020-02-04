#ifndef TOGGLE_ANIMATIONS_H
#define TOGGLE_ANIMATIONS_H

#include "GameEvent.h"

//Toggle anim class for making animations stop and or resume
class ToggleAnimEvent : public Event
{
public:

	// Constructors
	ToggleAnimEvent() :Event((EventType)TOGGLE_ANIMATION) {};

	// Destructors
	~ToggleAnimEvent() {};

private:
};

#endif

