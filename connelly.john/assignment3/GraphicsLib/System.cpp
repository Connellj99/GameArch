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

#include "System.h"

enum Keys
{
	F = ALLEGRO_KEY_F,
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	ESC = ALLEGRO_KEY_ESCAPE
	 
};

System::System()
{

}

System::~System()
{

}

/*ALLEGRO_MOUSE_STATE state;

 al_get_mouse_state(&state);
if (state.buttons & 1) {
	 //Primary (e.g. left) mouse button is held. 
	printf("Mouse position: (%d, %d)\n", state.x, state.y);
}
if (state.buttons & 2) {
	 //Secondary (e.g. right) mouse button is held. 
}
if (state.buttons & 4) {
	//Tertiary (e.g. middle) mouse button is held. 
}
*/
