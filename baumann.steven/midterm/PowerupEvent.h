#pragma once
#ifndef POWERUP_EVENT_H
#define POWERUP_EVENT_H

#include <Vector2D.h>
#include "Event.h"

enum PowerupType { INVALID_PU_TYPE = -1, APPLE_EATEN, SLOW_DOWN, SPEED_UP, BONUS_POINTS, NUM_PU_TYPES };

class PowerupEvent :public Event
{
private:
	PowerupType ptType;

public:


	PowerupEvent(const PowerupType& mb);
	~PowerupEvent();

	PowerupType getButtonType() const { return ptType; }
};

#endif