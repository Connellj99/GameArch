#pragma once

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	MOUSE_CLICK_EVENT,
	MOUSE_MOVE_EVENT,
	KEY_DOWN_EVENT,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] = {  "Mouse Click Event",
													"Key Down Event"
												 };

class Event : public Trackable
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;
};