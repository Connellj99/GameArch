#pragma once

#include <string>
#include <trackable.h>

// Local includes
#include "Event.h"

using namespace std;

// Game Event Type Enum
enum GameEventType
{
	STOP_START_ANIMATION = NUM_EVENT_TYPES,
	SWITCH_ANIMATIONS,
	QUIT_GAME,
	CREATE_UNITS,
	DELETE_UNITS,
	MOVE_PLAYER,
	SHOOT_BULLET,
	START_GAME,
	MAKE_PLAYER_JUMP,
	MOVE_PLAYER_RIGHT,
	MOVE_PLAYER_LEFT
};