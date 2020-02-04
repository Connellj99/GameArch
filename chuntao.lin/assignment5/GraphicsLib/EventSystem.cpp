#include "EventSystem.h"
#include "Event.h"
#include "EventListener.h"

EventSystem * EventSystem::mspEventSysInstance = nullptr;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

void EventSystem::addListener(EventType type, EventListener* pEventListener)
{
	mListenerMap.insert( pair< EventType, EventListener* >(type, pEventListener) );
}

void EventSystem::removeListener(EventType type, EventListener *pEventListener)
{
	pair<multimap<EventType,EventListener*>::iterator,multimap<EventType,EventListener*>::iterator> ret;

	ret = mListenerMap.equal_range( type );
	multimap<EventType,EventListener*>::iterator iter;

	for( iter = ret.first; iter != ret.second; ++iter )
	{
		if( iter->second == pEventListener )
		{
			mListenerMap.erase( iter );
			break;//to prevent using invalidated iterator
		}
	}
}

void EventSystem::removeListenerFromAllEvents( EventListener* pEventListener )
{
	multimap<EventType,EventListener*>::iterator iter;

	bool allTheWayThrough = false;

	while( !allTheWayThrough )
	{
		allTheWayThrough = true;
		for( iter = mListenerMap.begin(); iter != mListenerMap.end(); ++iter )
		{
			if( iter->second == pEventListener )
			{
				mListenerMap.erase( iter );
				allTheWayThrough = false; //didn't make it the whole way through
				break;//to prevent using invalidated iterator
			}
		}
	}
}

EventSystem * EventSystem::getStaticEventSysInstance()
{
	assert(mspEventSysInstance != nullptr);
	return mspEventSysInstance;
}

void EventSystem::initStaticEventSysInstance()
{
	mspEventSysInstance = new EventSystem;
}

void EventSystem::cleanup()
{
	
}

void EventSystem::destroyStaticEventSysInstance()
{
	// This function destroys the current instance of the static class
	delete mspEventSysInstance;

}

void EventSystem::fireEvent( const Event& chosenEvent )
{
	mDispatchAllEvents( chosenEvent );
}

void EventSystem::mDispatchAllEvents( const Event& passedEvent )
{
	pair<multimap<EventType,EventListener*>::iterator,multimap<EventType,EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range( passedEvent.getType() );

	multimap<EventType,EventListener*>::iterator iter;
	for( iter = ret.first; iter != ret.second; ++iter )
	{
		iter->second->handleEvent( passedEvent );
	}

}