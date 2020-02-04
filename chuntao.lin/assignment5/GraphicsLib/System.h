#ifndef SYSTEM_H
#define SYSTEM_H

// Graphics Library includes
#include "GraphicsSystem.h"

// Input system 
#include "InputSystem.h"

// Non-standard library includes
#include <string>


//// Non-Allegro representation meant to
//// represent the current keyboard state
//enum Keys
//{
//	KEY_OTHER,
//	KEY_ESCAPE,
//	KEY_F,
//	KEY_S,
//	KEY_ENTER,
//	KEY_SPACE
//};
//
//// Non-Allegro representation meant to
//// represent the current mouse state
//enum Mouse_State 
//{
//	MOUSE_NONE,
//	MOUSE_LEFT,
//	MOUSE_RIGHT,
//	MOUSE_MIDDLE
//};

class System : public Trackable
{
public:

	// Constructors
	System();

	// Destructors
	~System();

	// Initializers
	void init( int screenWidth, int screenHeight );
	void initializeSystems();

	// Cleanups
	void cleanup();

	//Acessors
	/*Keys getKeyState();
	Mouse_State getMouseState();*/
	/*Vector2 getMousePosition();*/
	GraphicsSystem getGraphicsSystem();

	// Mutators
	void flipDisplay();

private:

	// Private Mutators
	//void updateMousePosition( Vector2 newPos );

	// Graphics Systems
	GraphicsSystem mCurrentGraphicsSystem;

	// Vector2's
	//Vector2 mMousePos;

	// Booleans
	bool mIsDisplaying;


};
#endif // !SYSTEM_H

