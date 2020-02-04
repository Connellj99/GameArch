#pragma once

#include "Event.h"

enum GameEventType
{
	EXIT_EVENT = NUM_EVENT_TYPES,
	SPAWN_EVENT,
	DELETE_EVENT,
	SPEED_CHANGE_EVENT,
	PAUSE_ANIM_EVENT,
	TOGGLE_ANIM_EVENT,
	MOVE_PLAYER_EVENT,
	SCORE_EVENT,
	DEATH_EVENT
};