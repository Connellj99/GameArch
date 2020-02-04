#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <Trackable.h>
#include "EventSystem.h"

class Event;
class EventSystem;

class EventListener : public Trackable
{
public:
	EventListener();
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

private:
	EventSystem* mpEventSystem;//the event system this lister is listening to
protected:
	EventSystem * getEventSystem() const { return mpEventSystem; };
};