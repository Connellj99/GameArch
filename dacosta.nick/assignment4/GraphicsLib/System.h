/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

#include <allegro5/allegro.h>

/// <summary>
///		Systems manager.
/// </summary>
/// <seealso cref="Trackable" />
class System :
	public Trackable
{
public:
	// Allow the game class to access member items.
	friend class Game;

	// Constructor.
	System();

	// Destructor.
	~System();

	// Initialize all the components required to run the system.
	void initialize(int _displayWidth, int _displayHeight);

	// Clean up all the initialized componenets.
	void cleanUp();

	// Get the state of the keyboard.
	void getKeyState();

	// Check if a specified key was pressed.
	bool checkKeyPressed(int _key);

	// Get the state of the mouse.
	void getMouseState();

	// Check if a mouse button was pressed.
	bool checkMouseButton(int _mouseButton);

	// Get the current mouse position.
	void getMousePosition(int& _positionX, int& _positionY);

	// Get the Graphics System.
	GraphicsSystem* getGraphicsSystem();

	// Get the input and update the graphics system.
	void update();

private:
	// Graphics system.
	GraphicsSystem* mpGraphicsSystem = nullptr;

	// Allegro keyboard state.
	ALLEGRO_KEYBOARD_STATE mKeyboardState;

	// Allegro mouse state.
	ALLEGRO_MOUSE_STATE mMouseState;
};