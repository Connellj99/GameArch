#pragma once
#include "Event.h"
#include "GameEvent.h"

class SwitchHead : public Event
{
public:
	SwitchHead() :Event((EventType)HEAD_SWITCH) {};
	~SwitchHead() {};
};