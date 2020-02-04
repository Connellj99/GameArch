/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "System.h"

System::System()
{
}

System::~System()
{
	this->cleanUp();
}

int System::init(int wide, int tall)
{
	if (mInit == false) 
	{
		if (!al_init())
		{
			cout << "error initting Allegro\n";
			return 1;
		}
		if (!al_init_image_addon())
		{
			cout << "error - Image Add-on not initted\n";
			return 1;
		}
		if (!al_init_font_addon())
		{
			cout << "error - Font Add-on not initted\n";
			return 1;
		}
		if (!al_init_ttf_addon())
		{
			cout << "error - TTF Add-on not initted\n";
			return 1;
		}
		if (!al_init_primitives_addon())
		{
			cout << "error - primitives Add-on not initted\n";
			return 1;
		}
		if (!al_install_audio())
		{
			cout << "error - Audio Add-on not initted\n";
			//return 1;
		}
		if (!al_init_acodec_addon())
		{
			cout << "error - Audio Codec Add-on not initted\n";
			//return 1;
		}
		if (!al_reserve_samples(1))
		{
			cout << "error - samples not reserved\n";
			//return 1;
		}

		if (!al_install_keyboard()) {
			cout << "failed to initialize the keyboard!\n";
			return 1;
		}

		if (!al_install_mouse()) {
			cout << "failed to initialize the mouse!\n";
			return 1;
		}

		mGraphics.init(wide, tall);

		mInit = true;
	}
	return 0;
	
}

int System::cleanUp()
{
	if (mInit)
	{
		mGraphics.cleanUp();
		mInit = false;
	}
	return 0;
}

bool System::getKeyState(KeyConvert key)
{
	ALLEGRO_KEYBOARD_STATE KeyState;
	al_get_keyboard_state(&KeyState);
	return al_key_down(&KeyState, key);
}

MouseState System::getMouseState()
{
	ALLEGRO_MOUSE_STATE state;

	al_get_mouse_state(&state);
	
	MouseState retState;

	retState.left = al_mouse_button_down(&state, 1);
	retState.right = al_mouse_button_down(&state, 2);
	retState.loc.x = al_get_mouse_state_axis(&state, 0);
	retState.loc.y = al_get_mouse_state_axis(&state, 1);

	return retState;
}

void System::rest(double time)
{
	al_rest(time);
}
