/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <map>

#include "Trackable.h"

#include "KeyCodes.h"
#include "EventTypes.h"

#include "Event.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"

#include "EventListener.h"
#include "EventSystem.h"
#include "InputSystem.h"



InputSystem::InputSystem()
{

	return;
}


InputSystem::~InputSystem()
{

	return;
}

// Initialize the input system.
void InputSystem::initialize()
{
	if (!al_init())
	{
		std::cout << "Error initializing Allegro!" << std::endl;
		return;
	}
	// Install the Allegro keyboard.
	if (!al_install_keyboard())
	{
		std::cout << "Error installing Allegro keyboard!" << std::endl;
		return;
	}

	// Install the Allegro mouse.
	if (!al_install_mouse())
	{
		std::cout << "Error installing Allegro mouse!" << std::endl;
		return;
	}
	return;
}

// Clean up the input system.
void InputSystem::cleanUp()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	return;
}

// Update the input system.
void InputSystem::update()
{
	EventSystem* pEventSystem = EventSystem::getInstance();

	getKeyState();
	getMouseState();

	checkKeys();
	pEventSystem->performEvent(KeyboardEvent(mKeys));
	

	checkMouse();
	pEventSystem->performEvent(MouseEvent(mMousePositionX, mMousePositionY, mMouseButtons));

	return;
}

// Get the state of the keyboard.
void InputSystem::getKeyState()
{
	al_get_keyboard_state(&mKeyboardState);

	return;
}

// Check if any key was pressed.
bool InputSystem::checkKeys()
{
	bool keyPressed = false;

	for (size_t counter = 0; counter < KEY_MAX; counter++)
	{
		bool currentKey = al_key_down(&mKeyboardState, counter);
		mKeys[counter] = currentKey;

		if (currentKey)
		{
			keyPressed = true;
		}
	}

	return keyPressed;
}

// Get the state of the mouse.
void InputSystem::getMouseState()
{
	al_get_mouse_state(&mMouseState);

	return;
}

// Check if any mouse button is pressed and get the position of the mouse.
bool InputSystem::checkMouse()
{
	bool buttonPressed = false;

	for (size_t counter = 0; counter < MOUSE_MAX; counter++)
	{
		bool currentButton = al_mouse_button_down(&mMouseState, counter);
		mMouseButtons[counter] = currentButton;

		if (currentButton)
		{
			buttonPressed = true;
		}
	}

	mMousePositionX = mMouseState.x;
	mMousePositionY = mMouseState.y;

	return buttonPressed;
}

bool InputSystem::checkMouseMovement()
{
	if (mMouseState.x != mMousePositionX || mMouseState.y != mMousePositionY)
	{
		return true;
	}

	return false;
}

// Get the current mouse position.
void InputSystem::getMousePosition(int& _positionX, int& _positionY)
{
	_positionX = mMouseState.x;
	_positionY = mMouseState.y;
	return;
}
