#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class TurnRightEvent : public Event
{
private:

public:
	TurnRightEvent() :Event((EventType)TURN_RIGHT_EVENT) {};
	~TurnRightEvent() {};
};