#pragma once
#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <map>
#include "Event.h"
#include <Trackable.h>

class EventListener;

using namespace std;

class EventSystem :public Trackable 
{
private:
	multimap< EventType, EventListener* > mListenerMap;
	static bool mIsCleaned;
	void dispachAllEvents(const Event& theEvent);

	EventSystem();
	~EventSystem();

	EventSystem(EventSystem& es) = delete;
	static EventSystem* mpEventSystem;
public:
	static void createInstance();
	static EventSystem* getInstance();
	static void cleanupInstance();
	void cleanup();
	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

};

#endif