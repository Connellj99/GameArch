#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <Trackable.h>

class Event;
class EventSystem;

class EventListener:public Trackable
{
public:
	EventListener();//the default constructor
	EventListener(EventSystem* passedEventSystem);//the constructor that takes in a event system
	
	virtual ~EventListener();

	virtual void handleEvent( const Event& theEvent ) = 0;

private:
	EventSystem * mpEventSys;//the event system this lister is listening to. I decided to keep these two lines in
protected:
	EventSystem * mpGetEventSystem() const { return mpEventSys; };
};
#endif