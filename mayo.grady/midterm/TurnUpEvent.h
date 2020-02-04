#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class TurnUpEvent : public Event
{
private:

public:
	TurnUpEvent() :Event((EventType)TURN_UP_EVENT) {};
	~TurnUpEvent() {};
};