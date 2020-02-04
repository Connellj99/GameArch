#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "GraphicsSystem.h"
#include "EventSystem.h"
#include "LeftMouseEvent.h"
#include "RightMouseEvent.h"

enum Keys
{
	F_KEY = ALLEGRO_KEY_F,
	S_KEY = ALLEGRO_KEY_S,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	ESC_KEY = ALLEGRO_KEY_ESCAPE,
	SPACE_KEY = ALLEGRO_KEY_SPACE
};

class InputSystem : public Trackable
{
private:
	bool mIsInitted = false;

	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	int mMouseButton;
	int mMouseX;
	int mMouseY;

public:
	//init
	void init();

	//cleanup
	void cleanup();

	//constructor
	InputSystem();

	//destructor
	~InputSystem();

	//update
	void update();

	//accessors for mouse info
	int getMouseButton() { return mMouseButton; };
	int getMouseX() { return mMouseX; };
	int getMouseY() { return mMouseY; };
};