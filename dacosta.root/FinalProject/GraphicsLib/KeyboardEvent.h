/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class KeyboardEvent :
	public Event
{
public:
	// Create a new keyboard event.
	KeyboardEvent(bool _keys[KEY_MAX]);

	// Get the key.
	void getKeys(bool _keys[KEY_MAX]);

private:
	// The keys.
	bool mKeys[KEY_MAX] = { false };
};