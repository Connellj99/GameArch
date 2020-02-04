#pragma once

#include <map>
#include <Trackable.h>

/*
Create additional Events and determine/create appropriate listeners for Adding units/deleting
units/(Un)Freezing all animations/Quitting the game
Make the EventSystem a “static” class which is initted and cleaned up in main.cpp
*/
class Event;
enum EventType;
class EventListener;

using namespace std;

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

	//static EventSystem* msInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents(const Event& theEvent);
};
