#ifndef  EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include  "Trackable.h"
#include <map>
#include "Event.h"

class EventListener;

class EventSystem : public Trackable
{
public:
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener);
	void removeListenerFromAllEvents(EventListener* pListener);

private:
	static EventSystem* mpsInstance;

	EventSystem();
	~EventSystem();

	std::multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents(const Event& theEvent);

};
#endif