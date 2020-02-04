#pragma once
#include "Event.h"
#include "GameEvent.h"

class Difficulty_Menu : public Event
{
public:
	Difficulty_Menu() :Event((EventType)D_KEY) {};
	~Difficulty_Menu() {};
};