#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <map>
#include <cassert>
#include "Trackable.h"
#include "Event.h"
#include "EventListener.h"

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem : public Trackable
{
private:
	static EventSystem * mpsInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents(const Event& theEvent);

	EventSystem();
	~EventSystem();

public:
	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener);
	void removeListenerFromAllEvents(EventListener* pListener);

	//static functions
	static EventSystem * getInstance() { assert(mpsInstance != nullptr); return mpsInstance; };
	static void initInstance() { mpsInstance = new EventSystem; };
	static void cleanupInstance() { delete mpsInstance; };
};