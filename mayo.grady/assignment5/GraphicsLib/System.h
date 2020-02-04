#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "InputSystem.h"

class System : public Trackable
{
private:
	//Graphics System object
	GraphicsSystem * mpGraphicsSystem;

	//Other data as necessary
	bool mIsInitted = false;

	InputSystem * mpInputSystem;

public:	
	//constructor
	System();

	//destructor
	~System();

	//init
	void init(int width, int height);

	//cleanup
	void cleanup();

	//Create a buffer from a image file
	GraphicsBuffer * createBuffer(string filename);

	//get graphics system objecct to be able to use draw functions
	GraphicsSystem * getGraphicsSystem() { return mpGraphicsSystem; };

	InputSystem * getInputSystem() { return mpInputSystem; };
};