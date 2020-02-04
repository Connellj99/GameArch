#pragma once

#include "Event.h"

enum GameEventType
{
	EXIT = NUM_EVENT_TYPES,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ADD,
	COLLIDE
};