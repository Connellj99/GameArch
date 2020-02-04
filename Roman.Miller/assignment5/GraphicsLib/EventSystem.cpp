#include "EventSystem.h"
#include "Event.h"
#include "EventListener.h"
#include <assert.h>
using namespace std;

EventSystem* EventSystem::mpsEventSystem = nullptr;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

EventSystem * EventSystem::getInstance()
{
	return mpsEventSystem;
}

void EventSystem::initInstance()
{
	if (mpsEventSystem == nullptr)
	{
		mpsEventSystem = new EventSystem;
	}
	else
	{
		assert(mpsEventSystem != nullptr);
	}
}

void EventSystem::cleanupInstance()
{
	delete mpsEventSystem;
	mpsEventSystem = nullptr;
}

void EventSystem::fireEvent(const Event& event)
{
	dispatchAllEvents(event);
}

void EventSystem::addListener(EventType type, EventListener * listener)
{
	mListenerMap.insert(pair<EventType, EventListener*>(type, listener));
}

void EventSystem::removeListener(EventType type, EventListener * listener)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range(type);
	multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter)
	{
		if (iter->second == listener)
		{
			mListenerMap.erase(iter);
			break;
		}
	}
}

void EventSystem::removeListenerFromAllEvents(EventListener * listener)
{
	multimap<EventType, EventListener*>::iterator iter;
	bool finished = false;

	while (!finished)
	{
		finished = true;
		for (iter = mListenerMap.begin(); iter != mListenerMap.end(); ++iter)
		{
			if (iter->second == listener)
			{
				mListenerMap.erase(iter);
				finished = false; 
				break;
			}
		}
	}
}

void EventSystem::dispatchAllEvents(const Event& event)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range(event.getType());

	multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter)
	{
		iter->second->handleEvent(event);
	}
}
