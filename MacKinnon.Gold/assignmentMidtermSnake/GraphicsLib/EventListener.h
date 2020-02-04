#pragma once
#include <Trackable.h>

class Event;
class EventSystem;

class EventListener : public Trackable
{
public:
	EventListener();
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

	virtual void cleanup();

private:
	EventSystem* mpEventSystem;
protected:
	EventSystem * getEventSystem() const { return mpEventSystem; };
};

