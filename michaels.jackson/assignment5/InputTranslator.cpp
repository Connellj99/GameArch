/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "InputTranslator.h"

InputTranslator::InputTranslator(EventSystem* pEventSystem): EventListener(pEventSystem)
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
	if (theEvent.getType() == MOUSEIN_EVENT)
	{
		const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
		const MouseState state = mouseEvent.getState();
		if (state.left)
		{
			SpawnEvent ev(state.loc);
			EventSystem::getInstance()->fireEvent(ev);
		}
		if (state.right)
		{
			DeleteEvent ev(state.loc);
			EventSystem::getInstance()->fireEvent(ev);
		}
	}
	else if (theEvent.getType() == KEYBOARD_EVENT)
	{
		KeyEvent keyEvent = (KeyEvent&)(theEvent);
		switch (keyEvent.getKey())
		{
		case KEY_F:
			break;

		case KEY_S:
			break;

		case KEY_ENTER:
			getEventSystem()->fireEvent(ChangeEvent());
			break;

		case KEY_SPACE:
			getEventSystem()->fireEvent(StopEvent());
			break;

		case KEY_ESCAPE:
			getEventSystem()->fireEvent(ExitEvent());
			break;
		}
	}
}