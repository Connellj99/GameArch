/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <map>
#include <iostream>
#include <cassert>

#include "Trackable.h"

#include "EventTypes.h"

#include "Event.h"
#include "EventListener.h"
#include "EventSystem.h"

EventSystem* EventSystem::smpInstance = nullptr;

// Get the instance.
EventSystem* EventSystem::getInstance()
{
	// Make sure the instance exists first.
	assert(smpInstance != nullptr);

	// Return the instance.
	return smpInstance;
}

// Initialize the instance.
void EventSystem::initializeInstance()
{
	// Create a new instance of game if it doesn't exist.
	if (smpInstance == nullptr)
	{
		smpInstance = new EventSystem;
	}

	return;
}

// Clean up the instance.
void EventSystem::cleanUpInstance()
{
	delete smpInstance;
	smpInstance = nullptr;

	return;
}

// Perform the event given.
void EventSystem::performEvent(const Event& _theEvent)
{
	dispatchAllEvents(_theEvent);

	return;
}

// Add a listener to the system.
void EventSystem::addListener(EventType _type, EventListener * _pListener)
{
	mListenerMultiMap.insert(std::pair<EventType, EventListener*>(_type, _pListener));

	return;
}

// Remove a listener from the system.
void EventSystem::removeListener(EventType _type, EventListener * _pListener)
{
	std::pair<std::multimap<EventType, EventListener*>::iterator, std::multimap<EventType, EventListener*>::iterator> ret;

	ret = mListenerMultiMap.equal_range(_type);
	std::multimap<EventType, EventListener*>::iterator iterator;

	for (iterator = ret.first; iterator != ret.second; ++iterator)
	{
		if (iterator->second == _pListener)
		{
			mListenerMultiMap.erase(iterator);
			return;
		}
	}

	return;
}

// Remove a listener from all the events.
void EventSystem::removeListenerFromAllEvents(EventListener * _pListener)
{
	std::multimap<EventType, EventListener*>::iterator iterator;

	bool allTheWayThrough = false;

	while (!allTheWayThrough)
	{
		allTheWayThrough = true;

		for (iterator = mListenerMultiMap.begin(); iterator != mListenerMultiMap.end(); ++iterator)
		{
			if (iterator->second == _pListener)
			{
				mListenerMultiMap.erase(iterator);
				allTheWayThrough = false; //didn't make it the whole way through
				break;//to prevent using invalidated iterator
			}
		}
	}

	return;
}

// Dispatch all the specified events.
void EventSystem::dispatchAllEvents(const Event& _theEvent)
{
	std::pair<std::multimap<EventType, EventListener*>::iterator, std::multimap<EventType, EventListener*>::iterator> ret;
	
	ret = mListenerMultiMap.equal_range(_theEvent.getType());

	std::multimap<EventType, EventListener*>::iterator iterator;

	for (iterator = ret.first; iterator != ret.second; ++iterator)
	{
		iterator->second->handleEvent(_theEvent);
	}

	return;
}
