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
	EventSystem();
	~EventSystem();

	void fireEvent( const Event& theEvent );
	void addListener( EventType type, EventListener* pListener );
	void removeListener( EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

	static EventSystem* getInstance() { assert(msInstance != nullptr); return msInstance; };
	static void initSystem() { msInstance = new EventSystem; };
	static void deleteInstance() { delete msInstance; };

private:
	static EventSystem* msInstance;

	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents( const Event& theEvent );

};

