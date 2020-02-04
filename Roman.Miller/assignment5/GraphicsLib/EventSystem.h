#pragma once

#include <map>
#include <Trackable.h>
#include "InputSystem.h"

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

	void fireEvent(const Event& event);

	void addListener(EventType type, EventListener* listener);

	void removeListener(EventType type, EventListener* listener);
	void removeListenerFromAllEvents(EventListener* listener);

private:
	EventSystem();
	~EventSystem();
	multimap<EventType, EventListener*> mListenerMap;

	static EventSystem* mpsEventSystem;

	void dispatchAllEvents(const Event& event);
};