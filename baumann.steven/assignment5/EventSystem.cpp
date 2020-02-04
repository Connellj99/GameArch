#include "EventSystem.h"
#include "EventListener.h"

EventSystem* EventSystem::mpEventSystem = nullptr;
bool EventSystem::mIsCleaned = false;

EventSystem::EventSystem()
{
}
EventSystem::~EventSystem()
{
	cleanup();
	
}

void EventSystem::addListener(EventType type, EventListener* pListener)
{
	mListenerMap.insert(pair<EventType, EventListener*>(type, pListener));
}

void EventSystem::removeListener(EventType type, EventListener* pListener)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;

	ret = mListenerMap.equal_range(type);
	multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter)
	{
		if (iter->second == pListener)
		{
			mListenerMap.erase(iter);
			break;
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
				allTheWayThrough = false;
				break;
			}
		}
	}
}

void EventSystem::fireEvent(const Event& theEvent)
{
	dispachAllEvents(theEvent);
}

void EventSystem::dispachAllEvents(const Event& theEvent)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range( theEvent.getType() );

	multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter)
	{
		iter->second->handleEvent( theEvent );
	}

}

void EventSystem::createInstance()
{
	if (mpEventSystem == nullptr)
	{
		mpEventSystem = new EventSystem();
	}
}

EventSystem* EventSystem::getInstance() 
{
	if (mpEventSystem != nullptr)
	{
		return mpEventSystem;
	}
	return nullptr;
}

void EventSystem::cleanupInstance()
{
	if (mpEventSystem != nullptr)
	{
		mpEventSystem = nullptr;
	}
}

void EventSystem::cleanup()
{
	if (!mIsCleaned)
	{
		mIsCleaned = true;
		delete(this);
	}
}