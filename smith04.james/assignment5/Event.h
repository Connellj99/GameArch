#pragma once

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	ADD_EVENT,
	DELETE_EVENT,
	EXIT_EVENT, 
	FREEZE_EVENT,
	BUTTON_PRESS_EVENT,
	MOUSE_PRESS_EVENT,
	DEAN_EVENT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = {	"Add Event", "Delete Event", "Exit Event", "Freeze Event", "Button Press Event", "Mouse Press Event", "Dean Event"};

class Event :public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};