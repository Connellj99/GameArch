#ifndef GAME_EVENT_H
#define GAME_EVENT_H
#include "Event.h"

enum GameEventType
{
	PLAYER_MOVE_EVENT = NUM_EVENT_TYPES,
	PLAYER_SHOOT_EVENT,
	INIT_MUSHROOM_EVENT,
	MUSHROOM_DESTROYED_EVENT,
	SEGMENT_DESTROYED_EVENT,
	CENTIPEDE_KILLED_EVENT,
	PLAYER_LOSE_LIFE_EVENT,
	PLAY_EVENT,
	EXIT_GAME_EVENT
};
#endif