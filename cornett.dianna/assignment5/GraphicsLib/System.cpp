/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "System.h"


/*
Create a new System object
*/
System::System()
{

}

/*
Destructor calls clean up
*/
System::~System() 
{
	cleanUp();
}

/*
Init everything
*/
void System::init(int width, int height)
{
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->init(width, height);

	if (!al_install_keyboard()) 
	{
		std::cout << "Failed to install keyboard\n";
	}

	if (!al_install_mouse())
	{
		std::cout << "Failed to install mouse\n";
	}

}

/*
Delete all memory that was allocated
*/
void System::cleanUp()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	delete mpGraphicsSystem;
}

/*
Get wether or not a key is pressed 
*/
bool System::getKeyState(KeyCode keyCode)
{
	al_get_keyboard_state(&mKeyState);
	return al_key_down(&mKeyState, keyCode);
}

/*
Get wether or not mouse is pressed 
*/
bool System::getMouseState(MouseCode mouseButtonCode)
{
	al_get_mouse_state(&mMouseState);
	
	return mMouseState.buttons & mouseButtonCode;
}

/*
Get the graphics system that the system holds
*/
GraphicsSystem * System::getGraphicsSystem() 
{
	return mpGraphicsSystem;
}

/*
Return the position of the mouse
*/
Position System::getMousePosition() 
{
	al_get_mouse_state(&mMouseState);
	Position pos(mMouseState.x, mMouseState.y);
	return pos;
}

