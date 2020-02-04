#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/


#include "Trackable.h"
#include "GraphicsSystem.h"

enum Keys
{
	F_KEY = ALLEGRO_KEY_F,
	S_KEY = ALLEGRO_KEY_S,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	ESC_KEY = ALLEGRO_KEY_ESCAPE,
	SPACE_KEY = ALLEGRO_KEY_SPACE
};

class System : public Trackable
{
private:
	//Graphics System object
	GraphicsSystem * mpGraphicsSystem;

	//Other data as necessary
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	int mMouseButton;
	int mMouseX;
	int mMouseY;

	bool mIsInitted = false;

public:	
	//constructor
	System();

	//destructor
	~System();

	//init
	void init(int width, int height);

	//cleanup
	void cleanup();

	//get key state
	string getKeyState();

	//get mouse state
	void getMouseState();

	//Create a buffer from a image file
	GraphicsBuffer * createBuffer(string filename);

	//get graphics system objecct to be able to use draw functions
	GraphicsSystem * getGraphicsSystem() { return mpGraphicsSystem; };

	//accessors for mouse info
	int getMouseButton() { return mMouseButton; };
	int getMouseX() { return mMouseX; };
	int getMouseY() { return mMouseY; };
};