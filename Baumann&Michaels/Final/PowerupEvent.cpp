#include "PowerupEvent.h"

PowerupEvent::PowerupEvent(const PowerupType& pt)
	: Event(POWERUP_EATEN), ptType(pt)
{
}

PowerupEvent::~PowerupEvent()
{
}