#ifndef EventListener_h
#define EventListener_h
#include <Trackable.h>
#include "EventSystem.h"

class Event;
class EventSystem;

class EventListener:public Trackable
{
private:
	EventSystem* mEventSys;
protected:
	EventSystem* getEventSystem() const { return mEventSys; };

public:
	EventListener(EventSystem* eventSystem);
	virtual ~EventListener();

	virtual void calledEvent(const Event& event) = 0;
};
#endif // !EventListener_h