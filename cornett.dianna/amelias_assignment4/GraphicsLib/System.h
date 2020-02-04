/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include "GraphicsSystem.h"
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include "KeyCode.h"
#include "MouseCodes.h"
#include "Position.h"

class System : public Trackable
{
private:
	ALLEGRO_KEYBOARD_STATE mKeyState;
	ALLEGRO_MOUSE_STATE mMouseState;


	GraphicsSystem * mpGraphicsSystem;
	

public:

	/*
	Create a new System object
	*/
	System();

	/*
	Destructor calls clean up
	*/
	~System();

	/*
	Init graphics system and allegro functions
	*/
	void init(int width, int height);

	/*
	Delete all memory that was allocated and uninstall allegro stuff
	*/
	void cleanUp();

	/*
	Get the graphics system that the system holds
	*/
	GraphicsSystem * getGraphicsSystem();
	
	/*
	Get wether or not a key is pressed
	*/
	bool getKeyState(KeyCode keyCode);

	/*
	Get wether or not mouse is pressed
	*/
	bool getMouseState(MouseCode mouseButtonCode);

	/*
	Return the position of the mouse
	*/
	Position getMousePosition();

	
};