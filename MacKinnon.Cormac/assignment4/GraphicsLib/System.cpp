#include "System.h"


//constructor
System::System()
{
	
}

//destructor
System::~System()
{
	if (mIsInit) 
	{
		cleanup();
	}
}
//initialize the system and graphics system
void System::init(int width, int height)
{
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
	}
	if (!al_install_mouse())
	{
		std::cout << "error installing the mouse!\n";
	}
	if (!al_install_keyboard())
	{
		std::cout << "error installing the keyboard\n";
	}

	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->init(width, height);

	mIsInit = true;
}
//destroys program properly
void System::cleanup()
{
	delete mpGraphicsSystem;
	mIsInit = false;
}
//accessor for key states
bool System::getKeyState(int key)
{
	al_get_keyboard_state(&mKeyboardState);

	return al_key_down(&mKeyboardState, key);
}
//accessor for mouse state
bool System::getMouseState(int button) 
{
	al_get_mouse_state(&mMouseState);
	mMousePos = Vector2D(mMouseState.x, mMouseState.y);
	return al_mouse_button_down(&mMouseState, button);
}

//accessor for mouse posootpn
Vector2D System::getMousePos()
{
	return Vector2D(mMousePos);
}
//accessor for graphicsSystem
GraphicsSystem* System::getGraphicsSystem()
{
	return mpGraphicsSystem;
}
