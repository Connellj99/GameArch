#ifndef EVENT_H
#define EVENT_H

#include "Trackable.h"
#include <string>

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	MOVE_EVENT,
	STRING_EVENT,
	MOUSE_DOWN_EVENT,
	KEY_DOWN_EVENT,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] = { "Move Event",
												"String Event",
												"Mouse Down Event"
};

class Event : public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; }
	const std::string& getEventName() const;

private:
	EventType mType;

};
#endif EVENT_H