#include "EventSystem.h"
#include "EventListener.h"
#include "Event.h"

EventSystem* EventSystem::mpsEventSystem = nullptr;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

EventSystem * EventSystem::getInstance()
{
	assert(mpsEventSystem != nullptr);
	return mpsEventSystem;
}

void EventSystem::initInstance()
{
	mpsEventSystem = new EventSystem;
}

void EventSystem::cleanupInstance()
{
	delete mpsEventSystem;
}

void EventSystem::addListener(EventType type, EventListener* pListener)
{
	mpListenerMap.insert(pair<EventType, EventListener*>(type, pListener));
}

void EventSystem::removeListener(EventType type, EventListener* pListener)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;

	ret = mpListenerMap.equal_range(type);
	multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter) 
	{
		if (iter->second == pListener) 
		{
			mpListenerMap.erase(iter);
			break;
		}
	}

}

void EventSystem::removeListenerFromAllEvents(EventListener* pListener)
{
	multimap<EventType, EventListener*>::iterator iter;

	bool allThrough = false;

	while (!allThrough) 
	{
		allThrough = true;
		for (iter = mpListenerMap.begin(); iter != mpListenerMap.end(); ++iter) 
		{
			if (iter->second == pListener) 
			{
				mpListenerMap.erase(iter);
				allThrough = false;
				break;
			}
		}
	}
}

void EventSystem::fireEvent(const Event& theEvent)
{
	dispatchAllEvents(theEvent);
}

void EventSystem::dispatchAllEvents(const Event & theEvent)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;
	ret = mpListenerMap.equal_range(theEvent.getType());

	multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter) 
	{
		iter->second->handleEvent(theEvent);
	}
}
