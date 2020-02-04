#pragma once
#include <Trackable.h>
#include <map>
#include <cassert>

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem : public Trackable
{
public:
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener);
	void removeListenerFromAllEvents(EventListener* pListener);

	void fireEvent(const Event& theEvent);

private:
	static EventSystem* mpsEventSystem;

	EventSystem();
	~EventSystem();

	multimap<EventType, EventListener*> mpListenerMap;

	void dispatchAllEvents(const Event& theEvent);
};

