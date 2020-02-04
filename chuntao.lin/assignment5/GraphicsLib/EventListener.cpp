#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener()
{
}

EventListener::EventListener(EventSystem* passedEventSystem)
	:mpEventSys(passedEventSystem)
{
}

EventListener::~EventListener()
{
	mpEventSys->removeListenerFromAllEvents(this);
}
