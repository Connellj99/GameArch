#pragma once

#include <map>
#include <Trackable.h>

#include "Event.h"

class EventListener;
enum EventType;

using namespace std;

class EventSystem : public Trackable
{
public:
	static EventSystem* mpsEventSystem;

	// Instance
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanup();

	EventSystem();
	~EventSystem();

	void fireEvent( const Event& theEvent );
	void addListener( EventType type, EventListener* pListener );
	void removeListener( EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

private:
	//static EventSystem* msInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents( const Event& theEvent );
};

// Will just talk to translator (handleEvent)
// Then translator will fire new event
// Event system will then send to Game