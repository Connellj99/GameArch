/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <time.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "System.h"
#include "Game.h"


/***************************************************************************************
**									 INSTRUCTIONS									  **
** [X] Create a global Game object.                                                   **
** [X] Initialize the game object with an 800x600 display.                            **
** [X] Create a woods buffer.                                                         **
** [X] Create a smurf buffer.                                                         **
** [X] Create a dean buffer.                                                          **
** [X] Create smurf sprites.                                                          **
** [X] Create smurf sprite animation clip.                                            **
** [X] Create dean sprites.                                                           **
** [X] Create dean sprite animation clip.                                             **
** [X] Create a unit to store animation clips.                                        **
** [X] Place the unit in the center of the display.                                   **
** [X] Loop the game at 60fps.                                                        **
** [X] Draw the woods buffer as the background every frame.                           **
** [X] Draw the unit at the appropriate location with the appropriate animation clip. **
***************************************************************************************/

/*****************************************************************
**							CONTROLS							**
** [X] Left mouse down places unit at mouse location.           **
** [X] "F" key speeds up animation by a certain amount.         **
** [X] "S" key slows down animation by a certain amount.        **
** [X] "Enter" key switched between the smurf and dean sprites. **
** [X] "Escape" key exits the application.                      **
*****************************************************************/

// Display dimensions.
const int DISPLAY_WIDTH  = 800;
const int DISPLAY_HEIGHT = 600;

// Number of frames per second.
const double FRAME_RATE = 60;


int main()
{
	// Create a performance tracker.
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	// Create a new game.
	gpGame = new Game;

	// Initialize the game with a certain display size.
	gpGame->initialize(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// Loop the game at a given frame rate.
	gpGame->loop(FRAME_RATE);

	// Delete the game and performance tracker to free memory.
	delete gpGame;
	delete pPerformanceTracker;

	// Set the pointers to null.
	gpGame = nullptr;
	pPerformanceTracker = nullptr;

	// Print the memory allocation report.
	MemoryTracker::getInstance()->reportAllocations(std::cout);

	// Keep the console open.
	system("pause");

	return 0;
}