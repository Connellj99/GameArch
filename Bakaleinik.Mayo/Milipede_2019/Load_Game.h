#pragma once
#include "Event.h"
#include "GameEvent.h"

class Load_Game : public Event
{
public:
	Load_Game() :Event((EventType)L_KEY) {};
	~Load_Game() {};
};