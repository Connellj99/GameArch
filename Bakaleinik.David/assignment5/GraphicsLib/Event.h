#pragma once

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	SPACE,
	ENTER,
	ESCAPE,
	RIGHT_MOUSE_BUTTON,
	LEFT_MOUSE_BUTTON,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =	{	"Pause", "Switch head", "Quit", "Delete", "Create" };

class Event:public Trackable
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};