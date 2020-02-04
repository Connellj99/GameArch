/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventListener.h"

EventListener::EventListener(EventSystem* pEventSystem)
	:mpEventSystem(pEventSystem)
{
}

EventListener::EventListener()
{

}

EventListener::~EventListener()
{
	mpEventSystem->removeListenerFromAllEvents(this);
}