#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class TurnDownEvent : public Event
{
private:

public:
	TurnDownEvent() :Event((EventType)TURN_DOWN_EVENT) {};
	~TurnDownEvent() {};
};