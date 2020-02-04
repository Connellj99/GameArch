/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "InputTranslator.h"

InputTranslator::InputTranslator(EventSystem* pEventSystem) : EventListener(pEventSystem)
{
	mpEventSys = pEventSystem;
}


void InputTranslator::init()
{
	mpEventSys->addListener(MOUSEIN_EVENT, this);
	mpEventSys->addListener(KEYBOARD_EVENT, this);
}

void InputTranslator::cleanUp()
{

}



void InputTranslator::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == KEYBOARD_EVENT)
	{
		KeyEvent keyEvent = (KeyEvent&)(theEvent);
		switch (keyEvent.getKey())
		{
		case KEY_UP:
			getEventSystem()->fireEvent(MoveEvent(0));
			break;
		case KEY_RIGHT:
			getEventSystem()->fireEvent(MoveEvent(1));
			break;
		case KEY_DOWN:
			getEventSystem()->fireEvent(MoveEvent(2));
			break;
		case KEY_LEFT:
			getEventSystem()->fireEvent(MoveEvent(3));
			break;

		case KEY_SPACE:
			getEventSystem()->fireEvent(GrowEvent());
			break;

		case KEY_ENTER:
			getEventSystem()->fireEvent(ContinueEvent());
			break;
		case KEY_ESCAPE:
			getEventSystem()->fireEvent(ExitEvent());
			break;
		}
	}
}