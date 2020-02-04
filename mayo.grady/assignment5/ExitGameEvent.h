#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Event.h"
#include "GameEvent.h"

class ExitGameEvent : public Event
{
private:

public:
	ExitGameEvent() :Event((EventType)EXIT_GAME_EVENT) {};
	~ExitGameEvent() {};
};