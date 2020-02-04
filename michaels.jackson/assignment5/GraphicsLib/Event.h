/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	KEYBOARD_EVENT,
	MOUSEIN_EVENT,
	SPAWN_UNIT,
	DELETE_UNIT,
	STOP_ANIM,
	CHANGE_ANIM,
	EXIT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = { "Key Event", "MOUSE_EVENT", "SPAWN_UNIT", "DELETE_UNIT", "STOP_ANIM", "CHANGE_ANIM", "EXIT"
};

class Event : public Trackable
{
public:
	Event(EventType type = INVALID_EVENT_TYPE);
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};
#endif // !EVENT_H
