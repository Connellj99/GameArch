/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <vector>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"

#include "InputSystem.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "System.h"

// Constructor.
System::System()
{
	return;
}

// Destructor.
System::~System()
{
	cleanUp();
	return;
}

// Initialize all the components required to run the system.
void System::initialize(int _displayWidth, int _displayHeight)
{
	// Create a graphics system and initialize it.
	mpGraphicsSystem = new GraphicsSystem;
	mpGraphicsSystem->initialize(_displayWidth, _displayHeight);

	// Create an input system and initialize it.
	mpInputSystem = new InputSystem;
	mpInputSystem->initialize();

	return;
}

// Clean up all the initialized componenets.
void System::cleanUp()
{
	// Delete the input system if it isn't null.
	if (mpInputSystem != nullptr)
	{
		delete mpInputSystem;
	}

	// Delete the graphics system if it isn't null.
	if (mpGraphicsSystem != nullptr)
	{
		delete mpGraphicsSystem;
	}

	// Set the graphics pointer to null.
	mpGraphicsSystem = nullptr; 
	mpInputSystem    = nullptr; 

	return;
}

// Get the Graphics System.
GraphicsSystem * System::getGraphicsSystem()
{
	return mpGraphicsSystem;
}

// Update the graphics system.
void System::update()
{
	mpGraphicsSystem->update();
	mpInputSystem->update();
	return;
}