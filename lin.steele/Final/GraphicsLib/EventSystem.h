#pragma once

#include <map>
#include <Trackable.h>
#include <cassert>

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem:public Trackable
{
public:

	void fireEvent( const Event& theEvent );
	void addListener( EventType type, EventListener* pListener );
	void removeListener( EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

	static EventSystem* getStaticInstance();
	static void destroyStaticInstance();
	static void initStaticInstance();

private:
	// Constructors
	EventSystem();

	// Destructors
	~EventSystem();

	// Static instances
	static EventSystem* mpEventSystem;

	//static EventSystem* msInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents( const Event& theEvent );

};

