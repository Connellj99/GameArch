/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <time.h>
#include <assert.h>
#include <vector>
#include <map>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Trackable.h"

#include "LuaWrapper.hpp"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"
#include "EventTypes.h"
#include "DirectionKeys.h"
#include "UnitTypes.h"

#include "LuaScript.h"

#include "Event.h"

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "UnitEvents.h"
#include "GameEvents.h"

#include "EventListener.h"

#include "EventSystem.h"
#include "InputSystem.h"
#include "InputTranslator.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Level.h"
#include "LevelManager.h"
#include "Unit.h"
#include "Player.h"
#include "UnitManager.h"
#include "System.h"
#include "Game.h"


/*****************************************************************************************
**									 INSTRUCTIONS										**
** [X] Create a global Game object.														**
** [X] Initialize the game object with an 800x600 display.								**
** [X] Create a woods buffer.															**
** [X] Create a smurf buffer.															**
** [X] Create a dean buffer.															**
** [X] Create smurf sprites.															**
** [X] Create smurf sprite animation clip.												**
** [X] Create dean sprites.																**
** [X] Create dean sprite animation clip.												**
** [X] Create a unit to store animation clips.											**
** [X] Place the unit centered where the user left clicks.								**
** [X] Remove a unit where the user right clicks.										**
** [X] Loop the game at 60fps.															**
** [X] Space bar toggles all sprite animations on or off.	                            **
** [X] Enter key toggles last placed sprite between dean and smurf.						**
*****************************************************************************************/

/*********************************************************************************
**									CONTROLS									**
** [X] Left mouse down creates new unit at mouse location.						**
** [X] Right mouse down deletes the top unit at the mouses location.			**
** [X] "Enter" key switched between the smurf and dean sprites for last unit.	**
** [X] "Space" key toggles animation on/off for all units.						**
** [X] "Escape" key exits the application.										**
*********************************************************************************/

// Display dimensions.
const int GRID_WIDTH  = 26;
const int GRID_HEIGHT = 19;
const int CELL_WIDTH  = 32;
const int CELL_HEIGHT = 32;

// Number of frames per second.
const double FRAME_RATE = 60;


int main()
{
	// Create a performance tracker.
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	// Initialize the event system.
	EventSystem::initializeInstance();

	// Initialize the game instance.
	Game::initializeInstance();

	// Get the game singleton.
	Game* pGame = Game::getInstance();

	// Initialize the game with a certain display size.
	pGame->initialize(GRID_WIDTH, GRID_HEIGHT, CELL_WIDTH, CELL_HEIGHT);

	// Loop the game at a given frame rate.
	pGame->loop(FRAME_RATE);
	
	// Clean up the game instance.
	pGame->cleanUpInstance();

	EventSystem::cleanUpInstance();

	// Delete the performance tracker to free memory.
	delete pPerformanceTracker;

	// Set the pointers to null.
	pPerformanceTracker = nullptr;

	// Print the memory allocation report.
	MemoryTracker::getInstance()->reportAllocations(std::cout);

	// Keep the console open.
	system("pause");

	return 0;
}