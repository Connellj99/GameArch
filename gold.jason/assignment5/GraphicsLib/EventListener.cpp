#include "EventListener.h"

EventListener::EventListener(EventSystem* eventSys):mEventSys(eventSys)
{

}

EventListener::~EventListener()
{
	mEventSys->removeListenerFromAllEvents(this);
}