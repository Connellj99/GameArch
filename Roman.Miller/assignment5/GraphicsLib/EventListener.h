#pragma once
#include "Trackable.h"

class Event;
class EventSystem;

class EventListener : public Trackable
{
public:
	EventListener( EventSystem * eventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

private:
	EventSystem* mpEventSystem;
};
