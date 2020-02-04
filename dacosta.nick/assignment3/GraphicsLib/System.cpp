/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "System.h"

// Constructor.
System::System()
{
	return;
}

// Destructor.
System::~System()
{
	cleanUp();
	return;
}

// Initialize all the components required to run the system.
void System::initialize(int _displayWidth, int _displayHeight)
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

	// Create a graphics system and initialize it.
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->initialize(_displayWidth, _displayHeight);

	return;
}

// Clean up all the initialized componenets.
void System::cleanUp()
{
	// Delete the graphics system if it isn't null.
	if (mpGraphicsSystem != nullptr)
	{
		delete mpGraphicsSystem;
	}

	// Set the graphics pointer to null.
	mpGraphicsSystem = nullptr;

	return;
}

// TODO: Cache keyboard state in this function. Create is key pressed.
// Check if the specified key was pressed.
bool System::getKeyState(int _key)
{
	// Get the keyboard state.
	al_get_keyboard_state(&mKeyboardState);
	
	return al_key_down(&mKeyboardState, _key);
}

// TODO: Cache mouse state in this function. Create is mouse pressed.
// Get the current mouse state.
bool System::getMouseState(int _mouseButton)
{
	// Get the mouse state.
	al_get_mouse_state(&mMouseState);

	return al_mouse_button_down(&mMouseState, _mouseButton);
}

// Get the current mouse position.
void System::getMousePosition(int& _positionX, int& _positionY)
{
	_positionX = mMouseState.x;
	_positionY = mMouseState.y;
	return;
}

// Get the Graphics System.
GraphicsSystem * System::getGraphicsSystem()
{
	return mpGraphicsSystem;
}

// Update the graphics system.
void System::update()
{
	mpGraphicsSystem->update();
	return;
}