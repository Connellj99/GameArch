#pragma once
#include "Event.h"
#include "GameEvent.h"

class Options_Menu : public Event
{
public:
	Options_Menu() :Event((EventType)O_KEY) {};
	~Options_Menu() {};
};