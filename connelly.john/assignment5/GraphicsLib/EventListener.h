/*
Create additional Events and determine/create appropriate listeners for Adding units/deleting
units/(Un)Freezing all animations/Quitting the game
Make the EventSystem a “static” class which is initted and cleaned up in main.cpp
*/

#pragma once


#include  "Trackable.h"

class Event;
class EventSystem;


class EventListener :public Trackable
{
public:
	//EventListener();
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void cleanup();

	virtual void handleEvent(const Event& theEvent) = 0;
private:
	EventSystem* mpEventSystem;//the event system this lister is listening to
protected:
	EventSystem * getEventSystem() const { return mpEventSystem; };
	friend class EventSystem;
};

