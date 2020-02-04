#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Midterm
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class StartGameEvent : public Event
{
private:

public:
	StartGameEvent() :Event((EventType)START_GAME_EVENT) {};
	~StartGameEvent() {};
};