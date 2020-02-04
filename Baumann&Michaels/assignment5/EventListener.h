#pragma once
#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <Trackable.h>

class Event;
class EventSystem;

class EventListener :public Trackable 
{
private:
	EventSystem* mpEventSystem;
protected:
	EventSystem* getEventSystem() const { return mpEventSystem; }
public:
	EventListener(EventSystem* pEventSystem);
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;
};

#endif