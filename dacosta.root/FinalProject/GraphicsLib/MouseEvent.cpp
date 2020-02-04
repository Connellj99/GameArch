/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "KeyCodes.h"

#include "EventTypes.h"

#include "Event.h"
#include "MouseEvent.h"

// Create a new mouse event.
MouseEvent::MouseEvent(int _x, int _y, bool _buttons[MOUSE_MAX]) : Event(MOUSE)
{
	// Assign the position.
	mPositionX = _x;
	mPositionY = _y;

	// Assign the buttons.
	for (size_t counter = 0; counter < MOUSE_MAX; counter++)
	{
		mButtons[counter] = _buttons[counter];
	}

	return;
}

// Get the current mouse position.
void MouseEvent::getPosition(int& _x, int& _y)
{
	_x = mPositionX;
	_y = mPositionY;

	return;
}

// Get the mouse buttons.
void MouseEvent::getButtons(bool _buttons[MOUSE_MAX])
{
	for (size_t counter = 0; counter < MOUSE_MAX; counter++)
	{
		_buttons[counter] = mButtons[counter];
	}

	return;
}
