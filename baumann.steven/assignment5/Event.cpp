#include "Event.h"

Event::Event(EventType e) 
:mType(e) 
{
}
Event::~Event()
{
}

const string& Event::getEventName() const
{
	if (mType > INVALID_EVENT && mType < NUM_EVENT_TYPES) 
	{
		return EVENT_NAMES[mType];
	}
	else 
	{
		static const string nullstring;
		return nullstring;
	}
}