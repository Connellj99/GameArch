#ifndef SYSTEM_H
#define SYSTEM_H

#include "Trackable.h"
#include "GraphicsSystem.h"
#include <map>

/*
System
The class which holds the Graphics System and has functions to get keyboard/mouse state – part of
GraphicsLib project.
• The GraphicsSystem object
• Other data necessary to fulfill the requirements of the assignment
Public Functions
• Constructor/Destructor
• Init/Cleanup
• getKeyState, getMouseState
*/

class System : public Trackable
{
public:
	System();
	~System();

	void initialize();
	void cleanup();

	//getKeyState
	//getMouseState

private:
	ALLEGRO_MOUSE_STATE state;

};



#endif
