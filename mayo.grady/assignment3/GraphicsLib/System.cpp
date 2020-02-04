/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "System.h"

System::System()
{
	mpGraphicsSystem = new GraphicsSystem();
}

System::~System()
{
	cleanup();
}

void System::init(int width, int height)
{
	mIsInitted = true;
	mpGraphicsSystem->init(width, height);
	if (!al_install_keyboard())
	{
		cout << "error - Keyboard Add-on not initted";
	}
	if (!al_install_mouse())
	{
		cout << "error - Mouse Add-on not initted";
	}
}

void System::cleanup()
{
	if (mIsInitted)
	{
		mIsInitted = false;
		delete mpGraphicsSystem;
	}
}

string System::getKeyState()
{
	al_get_keyboard_state(&mKeyboardState);
	if (al_key_down(&mKeyboardState, F_KEY))
	{
		return "F";
	}
	if (al_key_down(&mKeyboardState, S_KEY))
	{
		return "S";
	}
	if (al_key_down(&mKeyboardState, ENTER_KEY))
	{
		return "ENTER";
	}
	if (al_key_down(&mKeyboardState, ESC_KEY))
	{
		return "ESC";
	}
	return "";
}

void System::getMouseState()
{
	al_get_mouse_state(&mMouseState);
	mMouseButton = mMouseState.buttons;
	mMouseX = mMouseState.x;
	mMouseY = mMouseState.y;
}

GraphicsBuffer * System::createBuffer(string filename)
{
	GraphicsBuffer * pBuffer = new GraphicsBuffer(filename);
	return pBuffer;
}