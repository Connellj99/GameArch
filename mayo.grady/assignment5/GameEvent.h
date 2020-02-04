#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"

enum GameEventType
{
	EXIT_GAME_EVENT = NUM_EVENT_TYPES,
	ADD_UNIT_EVENT,
	REMOVE_UNIT_EVENT,
	SWAP_ANIMATION_EVENT,
	TOGGLE_ANIMATION_EVENT
};