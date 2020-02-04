/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "EventSystem.h"
#include <trackable.h>
#include <allegro5/allegro.h>


class InputSystem : public Trackable
{
public:
	InputSystem() {}
	~InputSystem() { cleanUp(); }

	void init(EventSystem* eSystem) { pEventSystem = eSystem; }
	void cleanUp() {}
	void update();

	EventSystem* pEventSystem;

private:
	void getMouseState();
	void getKeyState();
	bool pressed_keys[ALLEGRO_KEY_MAX];
	ALLEGRO_KEYBOARD_STATE* mpKeyState;

};