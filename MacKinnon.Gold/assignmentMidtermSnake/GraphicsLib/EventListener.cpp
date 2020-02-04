#include "EventListener.h"
#include "EventSystem.h"



EventListener::EventListener()
{
}

EventListener::EventListener(EventSystem* pEventSystem)
	:mpEventSystem(pEventSystem)
{
}


EventListener::~EventListener()
{
	//mpEventSystem->removeListenerFromAllEvents(this);
}

void EventListener::cleanup()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
}
