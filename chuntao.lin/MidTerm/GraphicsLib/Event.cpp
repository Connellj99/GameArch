#include "Event.h"

Event::Event()
{
}

Event::Event(EventType type)
:mEventType(type)
{
}

Event::~Event()
{
}

const string& Event::getEventName() const
{
	if( mEventType > INVALID_EVENT && mEventType < NUM_EVENT_TYPES )
	{
		return EVENT_NAMES[mEventType];
	}
	else
	{
		static const string nullString;
		return nullString;
	}
}
