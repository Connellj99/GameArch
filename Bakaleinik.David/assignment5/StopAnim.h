#pragma once
#include "Event.h"
#include "GameEvent.h"

class StopAnimation : public Event
{
public:
	StopAnimation() :Event((EventType)STOP_ANIMATION) {};
	~StopAnimation() {};
};