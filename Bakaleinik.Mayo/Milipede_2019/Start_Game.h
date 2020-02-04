#pragma once
#include "Event.h"
#include "GameEvent.h"

class Start_Game : public Event
{
public:
	Start_Game() :Event((EventType)S_KEY) {};
	~Start_Game() {};
};