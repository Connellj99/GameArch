/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

#include <map>
#include <Trackable.h>
#include "KeyEvent.h"
#include "MouseEvent.h"
using namespace std;

class EventSystem;

class EventListener :public Trackable
{
public:
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

private:
	EventSystem* mpEventSystem;//the event system this lister is listening to
protected:
	EventSystem * getEventSystem() const { return mpEventSystem; };
};

static class EventSystem : public Trackable
{
public:
	static void initInstance() { mpInstance = new EventSystem(); };
	static void cleanupInstance() { delete mpInstance; };
	static EventSystem* getInstance() { assert(mpInstance != nullptr); return mpInstance; };
	

	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventListener* pListener, EventType type = INVALID_EVENT_TYPE);

private:
	static EventSystem* mpInstance;

	EventSystem();
	~EventSystem();
	multimap< EventType, EventListener* > mListeners;

	void dispatchAllEvents(const Event& theEvent);

};

