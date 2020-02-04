#ifndef EVENT_H
#define EVENT_H

#include "Trackable.h"

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	MOUSE_CLICK_EVENT,
	KEY_DOWN_EVENT,
	MOUSE_MOVE_EVENT,
	NUM_EVENT_TYPES
};

class Event : public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; }

private:
	EventType mType;

};
#endif EVENT_H