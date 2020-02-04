#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class ToggleAnimationEvent : public Event
{
private:

public:
	ToggleAnimationEvent() :Event((EventType)TOGGLE_ANIMATION_EVENT) {};
	~ToggleAnimationEvent() {};
};