#ifndef SYSTEM_H
#define SYSTEM_H

// Graphics Library includes
#include "GraphicsSystem.h"

// Non-standard library includes
#include <string>





// Non-Allegro representation meant to
// represent the current keyboard state
enum Keys
{
	key_other,
	key_escape,
	key_f,
	key_s,
	key_enter
};





// Non-Allegro representation meant to
// represent the current mouse state
enum Mouse_State 
{
	mouse_none,
	mouse_left,
	mouse_right,
	mouse_middle
};





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
	Keys getKeyState();
	Mouse_State getMouseState();
	Vector2 getMousePosition();
	GraphicsSystem getGraphicsSystem();

	// Mutators
	void flipDisplay();

private:

	// Private Mutators
	void updateMousePosition( Vector2 newPos );

	// Graphics Systems
	GraphicsSystem mCurrentGraphicsSystem;

	// Vector2's
	Vector2 mMousePos;

	// Booleans
	bool mIsDisplaying;

};



#endif // !SYSTEM_H

