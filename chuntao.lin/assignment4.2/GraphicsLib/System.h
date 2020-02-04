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
	key_enter,
	key_space,
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

	//allow user to choose if the left mouse should place new units, or just move the units.
	int getLeftMouseChoice() { return mLeftMouseChoice; };

	int leftMouseDraw() { return 0; };//returns 0
	int leftMouseMove() { return 1; };//returns 1

	//allow user to choose if the enter should toggle animations between all units or just last one
	int getEnterChoice() { return mEnterChoice; };

	int animationSwapAll() { return 0; };//returns 0
	int animationSwapLast() { return 1; }; //returns 1

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

	int mLeftMouseChoice;//used to determine with the system if left mouse should draw in a spot(0), or move an sprite(1).

	int mEnterChoice;//used to determine with the system if enter should swap animations on all(0), or just last unit placed(1)

	bool mKeyPressed = false;

	bool mMousePress = false;
};



#endif // !SYSTEM_H

