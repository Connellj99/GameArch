/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "InputTranslator.h"

InputTranslator::InputTranslator(EventSystem * pEventSystem)
	:EventListener(pEventSystem)
{
	mpEventSystem = pEventSystem;
}

InputTranslator::~InputTranslator()
{
	cleanup();
}

void InputTranslator::init()
{
	//cout << "Input translator" << endl;
	mIsInitted = true;
	mpEventSystem->addListener(LEFT_MOUSE_EVENT, this);
	mpEventSystem->addListener(RIGHT_MOUSE_EVENT, this);
	mpEventSystem->addListener(SPACE_KEY_EVENT, this);
	mpEventSystem->addListener(ENTER_KEY_EVENT, this);
	mpEventSystem->addListener(ESC_KEY_EVENT, this);
	mpEventSystem->addListener(UP_KEY_EVENT, this);
	mpEventSystem->addListener(DOWN_KEY_EVENT, this);
	mpEventSystem->addListener(LEFT_KEY_EVENT, this);
	mpEventSystem->addListener(RIGHT_KEY_EVENT, this);
	mpEventSystem->addListener(W_KEY_EVENT, this);
	mpEventSystem->addListener(A_KEY_EVENT, this);
	mpEventSystem->addListener(S_KEY_EVENT, this);
	mpEventSystem->addListener(D_KEY_EVENT, this);
}

void InputTranslator::cleanup()
{
	if (mIsInitted)
	{

	}
}

void InputTranslator::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == LEFT_MOUSE_EVENT)
	{
		const LeftMouseEvent& leftMouseEvent = static_cast<const LeftMouseEvent&>(theEvent);
		mpEventSystem->fireEvent(AddUnitEvent(leftMouseEvent.getLocation()));
	}
	if (theEvent.getType() == RIGHT_MOUSE_EVENT)
	{
		const RightMouseEvent& rightMouseEvent = static_cast<const RightMouseEvent&>(theEvent);
		mpEventSystem->fireEvent(RemoveUnitEvent(rightMouseEvent.getLocation()));
	}
	if (theEvent.getType() == SPACE_KEY_EVENT)
	{
		mpEventSystem->fireEvent(StartGameEvent());
	}
	if (theEvent.getType() == ENTER_KEY_EVENT)
	{
		mpEventSystem->fireEvent(SwapAnimationEvent());
	}
	if (theEvent.getType() == ESC_KEY_EVENT)
	{
		mpEventSystem->fireEvent(ExitGameEvent());
	}
	if (theEvent.getType() == UP_KEY_EVENT)
	{
		//cout << "IT-UP" << endl;
		mpEventSystem->fireEvent(TurnUpEvent());
	}
	if (theEvent.getType() == DOWN_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnDownEvent());
	}
	if (theEvent.getType() == LEFT_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnLeftEvent());
	}
	if (theEvent.getType() == RIGHT_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnRightEvent());
	}
	if (theEvent.getType() == W_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnUpEvent());
	}
	if (theEvent.getType() == A_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnLeftEvent());
	}
	if (theEvent.getType() == S_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnDownEvent());
	}
	if (theEvent.getType() == D_KEY_EVENT)
	{
		mpEventSystem->fireEvent(TurnRightEvent());
	}
}