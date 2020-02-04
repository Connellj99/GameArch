/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

enum EventType
{
	INVALID_EVENT_TYPE = -1,

	MOUSE,
	KEYBOARD,

	NUM_EVENT_TYPES
};

enum GameEventType
{
	EXIT = NUM_EVENT_TYPES,
	CREATE_UNIT,
	REMOVE_UNIT,
	TOGGLE_UNIT_ANIMATION,
	TOGGLE_UNIT_SPRITE,

	NUM_GAME_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] =
{
	"Move Event",
	"String Event"
};