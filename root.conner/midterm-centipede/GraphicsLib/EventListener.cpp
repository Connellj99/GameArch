#include "EventListener.h"
#include "EventSystem.h"

void EventListener::cleanup()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
}

EventListener::~EventListener()
{
	cleanup();
}