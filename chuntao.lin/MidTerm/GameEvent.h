#pragma once
#include "Event.h"

//holds the event types of the game.
enum GameEventType
{
	EXIT = NUM_EVENT_TYPES,
	CREATE,
	KILL,
	TOGGLE_ANIMATION,
	FLIP_ANIMATIONS,
	START,
	RESTART,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};
