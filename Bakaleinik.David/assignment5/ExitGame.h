#pragma once
#include "Event.h"
#include "GameEvent.h"

class ExitGame : public Event
{
public:
	ExitGame() :Event((EventType)EXIT_GAME) {};
	~ExitGame() {};
};