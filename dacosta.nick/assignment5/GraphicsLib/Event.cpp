/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "EventTypes.h"

#include "Event.h"



Event::Event(EventType _type)
{
	mType = _type;
	return;
}


Event::~Event()
{
	return;
}

// Get the event type.
EventType Event::getType() const
{
	return mType;
}

const std::string& Event::getEventName() const
{
	if (mType > INVALID_EVENT_TYPE && mType < NUM_EVENT_TYPES)
	{
		return EVENT_NAMES[mType];
	}
	else
	{
		static const std::string nullString;
		return nullString;
	}
}
