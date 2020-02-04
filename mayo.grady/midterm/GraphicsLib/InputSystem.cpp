/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "InputSystem.h"

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	//cout << "input system" << endl;
	mIsInitted = true;
	if (!al_install_keyboard())
	{
		cout << "error - Keyboard Add-on not initted";
	}
	if (!al_install_mouse())
	{
		cout << "error - Mouse Add-on not initted";
	}
}

void InputSystem::update()
{
	//cout << "I.S. update" << endl;
	al_get_mouse_state(&mMouseState);
	mMouseButton = mMouseState.buttons;
	mMouseX = mMouseState.x;
	mMouseY = mMouseState.y;
	al_get_keyboard_state(&mKeyboardState);
	if (mMouseButton == 1)
	{
		//cout << "left" << endl;
		//left mouse button event
		EventSystem::getInstance()->fireEvent(LeftMouseEvent(Vector2D(mMouseX, mMouseY)));
	}
	if (mMouseButton == 2)
	{
		//cout << "right" << endl;
		//right mouse button event
		EventSystem::getInstance()->fireEvent(RightMouseEvent(Vector2D(mMouseX, mMouseY)));
	}
	if (al_key_down(&mKeyboardState, SPACE_KEY))
	{
		//cout << "space" << endl;
		//space key event
		EventSystem::getInstance()->fireEvent(Event(SPACE_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, ENTER_KEY))
	{
		//cout << "enter" << endl;
		//enter key event
		EventSystem::getInstance()->fireEvent(Event(ENTER_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, ESC_KEY))
	{
		//cout << "esc" << endl;
		//escape key event
		EventSystem::getInstance()->fireEvent(Event(ESC_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, UP_KEY))
	{
		//cout << "up" << endl;
		//up key event
		EventSystem::getInstance()->fireEvent(Event(UP_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, DOWN_KEY))
	{
		//cout << "down" << endl;
		//down key event
		EventSystem::getInstance()->fireEvent(Event(DOWN_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, LEFT_KEY))
	{
		//cout << "left" << endl;
		//left key event
		EventSystem::getInstance()->fireEvent(Event(LEFT_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, RIGHT_KEY))
	{
		//cout << "right" << endl;
		//right key event
		EventSystem::getInstance()->fireEvent(Event(RIGHT_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, W_KEY))
	{
		//cout << "w" << endl;
		//w key event
		EventSystem::getInstance()->fireEvent(Event(W_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, A_KEY))
	{
		//cout << "a" << endl;
		//a key event
		EventSystem::getInstance()->fireEvent(Event(A_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, S_KEY))
	{
		//cout << "s" << endl;
		//s key event
		EventSystem::getInstance()->fireEvent(Event(S_KEY_EVENT));
	}
	if (al_key_down(&mKeyboardState, D_KEY))
	{
		//cout << "d" << endl;
		//D key event
		EventSystem::getInstance()->fireEvent(Event(D_KEY_EVENT));
	}
}

void InputSystem::cleanup()
{
	if (mIsInitted)
	{

	}
}