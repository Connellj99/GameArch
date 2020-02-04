#pragma once

#include <map>
#include <Trackable.h>

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem :public Trackable
{
public:
	static void initInstance();
	static void cleanUpInstance();
	static EventSystem* getEventSys();

	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener);
	void removeListenerFromAllEvents(EventListener* pListener);

private:
	EventSystem();
	~EventSystem();

	static EventSystem* mEventSys;
	multimap< EventType, EventListener* > mListenerMap;
	void dispatchAllEvents(const Event& theEvent);

};