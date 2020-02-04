/*
Conner Root
EGP 310 - 01
*/

#include "System.h"

System::System()
{
}

// Init / Cleanup
void System::init(int w, int h)
{
	if (!mInited)
	{
		al_init();
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		al_install_keyboard();
		al_install_mouse();

		mpGraphicSystem = new GraphicsSystem();
		mpGraphicSystem->init(w, h);
		mInited = true;
	}
}
void System::cleanup()
{
	if (mInited)
	{
		delete mpGraphicSystem;
		mInited = false;

		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		al_shutdown_ttf_addon();
	}
}

// Accessors
bool System::checkKeyDown(KeyCode key)
{
	al_get_keyboard_state(&mKeyState);

	return al_key_down(&mKeyState, key);
}

MouseState System::checkMouseDown()
{
	MouseState state;
	
	al_get_mouse_state(&mMouseState);

	state.clicked = al_mouse_button_down(&mMouseState, 1);
	state.xPos = mMouseState.x;
	state.yPos = mMouseState.y;

	return state;
}

// Wait function
void System::wait(float time)
{
	al_rest(time);
}

// Destructor
System::~System()
{
	cleanup();
}