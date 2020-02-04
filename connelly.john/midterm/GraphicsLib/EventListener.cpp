#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	EventListener::cleanup();
}

void EventListener::cleanup()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
}
