/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "EventSystem.h"

EventSystem* EventSystem::mpInstance = nullptr;

EventListener::EventListener(EventSystem* pEventSystem)
{
	mpEventSystem = pEventSystem;
}

EventListener::~EventListener()
{
	mpEventSystem->removeListener(this);
}



EventSystem::EventSystem()
{

}

EventSystem::~EventSystem()
{

}



void EventSystem::fireEvent(const Event& theEvent)
{
	dispatchAllEvents(theEvent);
}

void EventSystem::addListener(EventType type, EventListener* add)
{
	mListeners.insert(pair< EventType, EventListener* >(type, add));
}

void EventSystem::removeListener(EventListener* pListener, EventType type)										
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> target;	//make new pair of iterators

	if (type != INVALID_EVENT_TYPE)
	{
		target = mListeners.equal_range(type);																	//only look at given event type
		multimap<EventType, EventListener*>::iterator iter;															//make iterator

		bool allTheWayThrough = false;

		while (!allTheWayThrough)
		{
			allTheWayThrough = true;
			for (iter = target.first; iter != target.second; ++iter)													//iterate
			{
				if (iter->second == pListener)																			//find target
				{
					mListeners.erase(iter);																				//delete target
					allTheWayThrough = false;
					break;//to prevent using invalidated iterator
				}
			}
		}
	}
}

void EventSystem::dispatchAllEvents(const Event& theEvent)
{
	pair<multimap<EventType, EventListener*>::iterator, multimap<EventType, EventListener*>::iterator> target;
	target = mListeners.equal_range(theEvent.getType());

	multimap<EventType, EventListener*>::iterator iter;
	for (iter = target.first; iter != target.second; ++iter)
	{
		iter->second->handleEvent(theEvent);
	}
}