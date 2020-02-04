#include "Event.h"

Event::Event(EventType type)
{
	mType = type;
}

Event::~Event()
{
}

string Event::getEventName()
{
	if (mType > INVALID_EVENT_TYPE && mType < NUM_EVENT_SIZE)
	{
		return EVENT_NAMES[mType];
	}
	else
	{
		static const string nullString = NULL;
		return nullString;
	}
}
