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
	mpInputSystem = new InputSystem();
}

System::~System()
{
	cleanup();
}

void System::init(int width, int height)
{
	mIsInitted = true;
	mpGraphicsSystem->init(width, height);
	mpInputSystem->init();
}

void System::cleanup()
{
	if (mIsInitted)
	{
		mIsInitted = false;
		delete mpGraphicsSystem;
		delete mpInputSystem;
	}
}

GraphicsBuffer * System::createBuffer(string filename)
{
	GraphicsBuffer * pBuffer = new GraphicsBuffer(filename);
	return pBuffer;
}