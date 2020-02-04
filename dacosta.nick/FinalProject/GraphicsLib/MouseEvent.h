/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class MouseEvent :
	public Event
{
public:
	// Constructor.
	MouseEvent(int _x, int _y, bool _button[MOUSE_MAX]);

	// Get the mouse position.
	void getPosition(int& _x, int& _y);

	// Get the mouse button.
	void getButtons(bool _buttons[MOUSE_MAX]);

private:
	// The x position.
	int mPositionX = 0;
	// The y position.
	int mPositionY = 0;

	// The button.
	bool mButtons[MOUSE_MAX] = { false };
};

