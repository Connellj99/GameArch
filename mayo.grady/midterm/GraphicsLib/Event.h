#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <string>
#include "Trackable.h"

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	SPACE_KEY_EVENT,
	ENTER_KEY_EVENT,
	ESC_KEY_EVENT,
	LEFT_MOUSE_EVENT,
	RIGHT_MOUSE_EVENT,
	LEFT_KEY_EVENT,
	RIGHT_KEY_EVENT,
	UP_KEY_EVENT,
	DOWN_KEY_EVENT,
	W_KEY_EVENT,
	A_KEY_EVENT,
	S_KEY_EVENT,
	D_KEY_EVENT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = {

};

class Event : public Trackable
{
private:
	EventType mType;
public:
	Event(EventType type);
	virtual ~Event();
	EventType getType() const { return mType; };
	const string& getEventName() const;
};