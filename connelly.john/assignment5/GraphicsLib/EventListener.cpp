#include "EventListener.h"
#include "EventSystem.h"

/*
Create additional Events and determine/create appropriate listeners for Adding units/deleting
units/(Un)Freezing all animations/Quitting the game
Make the EventSystem a “static” class which is initted and cleaned up in main.cpp
*/

/*EventListener::EventListener()
{
}*/

EventListener::~EventListener()
{
	EventListener::cleanup();
}

void EventListener::cleanup()
{
	mpEventSystem->removeListenerFromAllEvents(this);

}


EventListener::EventListener(EventSystem* pEventSystem)
	:mpEventSystem(pEventSystem)
{
}


