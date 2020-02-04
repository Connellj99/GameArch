/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

#include "allegro5\allegro.h"

class InputSystem :
	public Trackable
{
public:
	InputSystem();
	~InputSystem();

	// Initialize the input system.
	void initialize();

	// Clean up the input system.
	void cleanUp();

	// Update the input system.
	void update();

private:

	// Get the state of the keyboard.
	void getKeyState();

	// Check if any key was pressed.
	bool checkKeys();
	
	// Get the state of the mouse.
	void getMouseState();

	// Check if any mouse button was pressed and get the mouse position.
	bool checkMouse();

	// Check if the mouse has moved.
	bool checkMouseMovement();

	// Get the current mouse position.
	void getMousePosition(int& _positionX, int& _positionY);

	// Allegro keyboard state.
	ALLEGRO_KEYBOARD_STATE mKeyboardState;

	// Allegro mouse state.
	ALLEGRO_MOUSE_STATE mMouseState;

	// All the keyboard keys.
	bool mKeys[KEY_MAX] = { false };

	// All the mouse buttons.
	bool mMouseButtons[MOUSE_MAX] = { false };

	// Mouse x position.
	int mMousePositionX = 0;

	// Mouse y position.
	int mMousePositionY = 0;
};

