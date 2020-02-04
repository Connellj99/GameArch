#pragma once
#include "Event.h"

enum GameEvents 
{
	CREATE_UNIT_EVENT = NUM_EVENT_TYPES, //remove from here and make a different enum in the main assignment area for the game specific events ex. create_unit_event = num_event_types, swap_animations, etc, num_game_event_types 
	SWAP_ANIMATION_EVENT,
	TOGGLE_ANIMATION_ACTIVE_EVENT,
	DESTROY_UNIT_EVENT,
	CHANGE_DIRECTION_EVENT,
	MOVE_DOWN_EVENT,
	MOVE_UP_EVENT,
	MOVE_LEFT_EVENT,
	MOVE_RIGHT_EVENT,
	START_GAME_EVENT,
	RESTART_EVENT,
	LEVEL_COMPLETE_EVENT,
	EXIT_GAME_EVENT
};