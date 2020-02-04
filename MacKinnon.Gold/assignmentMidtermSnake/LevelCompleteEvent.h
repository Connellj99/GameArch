#pragma once
#include "GameEvents.h"
#include "Event.h"
class LevelCompleteEvent : public Event
{
public:
	LevelCompleteEvent();
	~LevelCompleteEvent();
};

