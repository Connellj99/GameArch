#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class SwapAnimationEvent : public Event
{
private:

public:
	SwapAnimationEvent() :Event((EventType)SWAP_ANIMATION_EVENT) {};
	~SwapAnimationEvent() {};
};