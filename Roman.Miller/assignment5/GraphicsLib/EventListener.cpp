#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener(EventSystem * eventSystem)
{
	mpEventSystem = eventSystem;
}

EventListener::~EventListener()
{
	mpEventSystem->removeListenerFromAllEvents(this);
}
