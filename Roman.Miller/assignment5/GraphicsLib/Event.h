#pragma once
#include <string>
#include <Trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	CLICK_EVENT,
	KEY_EVENT,
	NUM_EVENT_SIZE // this is the size of the string array 
};

const string EVENT_NAMES[NUM_EVENT_SIZE] = { "Click Event", "Key Event" };


class Event : public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	string getEventName();

private:
	EventType mType;
};