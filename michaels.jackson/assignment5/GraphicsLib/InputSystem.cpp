/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "InputSystem.h"

void InputSystem::getKeyState()
{
	ALLEGRO_KEYBOARD_STATE KeyState;
	al_get_keyboard_state(&KeyState);
	if (al_key_down(&KeyState, ALLEGRO_KEY_F))
	{
		KeyEvent ev(KEY_F);
		EventSystem::getInstance()->fireEvent(ev);
	}
	if (al_key_down(&KeyState, ALLEGRO_KEY_S))
	{
		KeyEvent ev(KEY_S);
		EventSystem::getInstance()->fireEvent(ev);
	}
	if (al_key_down(&KeyState, ALLEGRO_KEY_ENTER))
	{
		KeyEvent ev(KEY_ENTER);
		EventSystem::getInstance()->fireEvent(ev);
	}
	if (al_key_down(&KeyState, ALLEGRO_KEY_ESCAPE))
	{
		KeyEvent ev(KEY_ESCAPE);
		EventSystem::getInstance()->fireEvent(ev);
	}
	if (al_key_down(&KeyState, ALLEGRO_KEY_SPACE))
	{
		KeyEvent ev(KEY_SPACE);
		EventSystem::getInstance()->fireEvent(ev);
	}
}

void InputSystem::getMouseState()
{
	ALLEGRO_MOUSE_STATE state;

	al_get_mouse_state(&state);

	MouseState retState;

	retState.left = al_mouse_button_down(&state, 1);
	retState.right = al_mouse_button_down(&state, 2);
	retState.loc.x = al_get_mouse_state_axis(&state, 0);
	retState.loc.y = al_get_mouse_state_axis(&state, 1);

	MouseEvent ev(retState);

	if (ev.getState().left || ev.getState().right)
	{
		EventSystem::getInstance()->fireEvent(ev);
	}
}

void InputSystem::update()
{
	getMouseState();
	getKeyState();
}