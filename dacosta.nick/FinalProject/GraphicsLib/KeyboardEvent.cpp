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
#include "KeyboardEvent.h"

// Create a new keyboard event.
KeyboardEvent::KeyboardEvent(bool _keys[KEY_MAX]) : Event(KEYBOARD)
{
	for (size_t counter = 0; counter < KEY_MAX; counter++)
	{
		mKeys[counter] = _keys[counter];
	}

	return;
}

// Get the keys.
void KeyboardEvent::getKeys(bool _keys[KEY_MAX])
{
	for (size_t counter = 0; counter < KEY_MAX; counter++)
	{
		_keys[counter] = mKeys[counter];
	}

	return;
}