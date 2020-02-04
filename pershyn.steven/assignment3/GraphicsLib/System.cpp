/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#include "System.h"

System::System()
{
	
}

System::~System()
{
	this->cleanUp();
}

int System::init(int width, int height)
{
	if (mInit == false)
	{
		if (!al_init())
		{
			cout << "Error initializing Allegro" << endl;
			return 1;
		}
		if (!al_init_image_addon())
		{
			cout << "error - Image Add-on not initted" << endl;
			return 1;
		}
		if (!al_init_font_addon())
		{
			cout << "error - Font Add-on not initted" << endl;
			return 1;
		}
		if (!al_init_ttf_addon())
		{
			cout << "error - TTF Add-on not initted" << endl;
			return 1;
		}
		if (!al_init_primitives_addon())
		{
			cout << "error - primitives Add-on not initted" << endl;
			return 1;
		}
		if (!al_install_audio())
		{
			cout << "error - Audio Add-on not initted" << endl;
			//return 1;
		}
		if (!al_init_acodec_addon())
		{
			cout << "error - Audio Codec Add-on not initted" << endl;
			//return 1;
		}
		if (!al_reserve_samples(1))
		{
			cout << "error - samples not reserved" << endl;
			//return 1;
		}
		if (!al_install_keyboard())
		{
			cout << "Error installing Allegro keyboard" << endl;
			return 1;
		}
		if (!al_install_mouse())
		{
			cout << "Error installing Allegro mouse" << endl;
			return 1;
		}
		mGraphics.Init(width, height);
		mInit = true;
	}
	return 0;
}

int System::cleanUp()
{
	if (mInit)
	{
		mGraphics.Cleanup();
		mInit = false;
	}
	return 0;
}

bool System::getKeyState(KeyConvert key)
{
	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);
	return al_key_down(&keyboardState, key);
}

MouseState System::getMouseState()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	MouseState retState;
	retState.left = al_mouse_button_down(&mouseState, 1);
	retState.right = al_mouse_button_down(&mouseState, 2);
	retState.loc.x = al_get_mouse_state_axis(&mouseState, 0);
	retState.loc.y = al_get_mouse_state_axis(&mouseState, 1);
	return retState;
}

void System::rest(double time)
{
	al_rest(time);
}


