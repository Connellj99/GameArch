#include "Event.h"

Event::Event(EventType type)
{
	mType = type;
}

Event::~Event() {}

const string& Event::getEventName() const
{
	if (mType >= NUM_EVENT_TYPES || mType <= INVALID_EVENT_TYPE)
	{
		static const string retNull;
		return retNull;
	}
	return EVENT_NAMES[mType];
}