#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <map>
#include <cassert>
#include <Trackable.h>

//forward declarations
class EventListener;
class Event;
enum EventType;

using namespace std;

class EventSystem:public Trackable
{
public:
	//initialize
	static void initStaticEventSysInstance();

	//the listener and firing event functionality
	void fireEvent(const Event& chosenEvent);
	void addListener(EventType type, EventListener* pEventListener);
	void removeListener(EventType type, EventListener* pEventListener);
	void removeListenerFromAllEvents(EventListener* pEventListener);

	//Cleanups
	void cleanup();
	static void destroyStaticEventSysInstance();
	
	// Acessors
	static EventSystem* getStaticEventSysInstance();

private:

	EventSystem();//the default construcot
	~EventSystem();//the destructor

	static EventSystem* mspEventSysInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void mDispatchAllEvents( const Event& passedEvent );
};
#endif

