#include "EventSystem.h"
#include <cassert>
#include "EventListener.h"
#include "Event.h"
//event would be the typical events for adding units and etc
/*
Create additional Events and determine/create appropriate listeners for Adding units/deleting
units/(Un)Freezing all animations/Quitting the game
Make the EventSystem a “static” class which is initted and cleaned up in main.cpp
*/

EventSystem* EventSystem::mpsInstance = nullptr;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

EventSystem* EventSystem::getInstance()
{
	assert(mpsInstance != nullptr);
	return mpsInstance;
}

void EventSystem::initInstance()
{
	if (mpsInstance == nullptr)
	{
		mpsInstance = new EventSystem();
	}
}

void EventSystem::cleanupInstance()
{
	delete mpsInstance;
}

void EventSystem::addListener(EventType type, EventListener* pListener)
{
	mListenerMap.insert(pair< EventType, EventListener* >(type, pListener));
}

void EventSystem::removeListener(EventType type, EventListener *pListener)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;

	ret = mListenerMap.equal_range(type);
	multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter)
	{
		if (iter->second == pListener)
		{
			mListenerMap.erase(iter);
			break;//to prevent using invalidated iterator
		}
	}
}

void EventSystem::removeListenerFromAllEvents(EventListener* pListener)
{
	multimap<EventType, EventListener*>::iterator iter;

	bool allTheWayThrough = false;

	while (!allTheWayThrough)
	{
		allTheWayThrough = true;
		for (iter = mListenerMap.begin(); iter != mListenerMap.end(); ++iter)
		{
			if (iter->second == pListener)
			{
				mListenerMap.erase(iter);
				allTheWayThrough = false; //didn't make it the whole way through
				break;//to prevent using invalidated iterator
			}
		}
	}
}

void EventSystem::fireEvent(const Event& theEvent)
{
	dispatchAllEvents(theEvent);
}

void EventSystem::dispatchAllEvents(const Event& theEvent)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range(theEvent.getType());

	multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter)
	{
		iter->second->handleEvent(theEvent);
	}

}