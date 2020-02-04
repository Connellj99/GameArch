/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <time.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsSystem.h"
#include "System.h"
#include "Game.h"
#include "Animation.h"

using namespace std;

// Display dimensions.
const int DISPLAY_WIDTH  = 800;
const int DISPLAY_HEIGHT = 600;

// Asset locations and names.
const string ASSET_PATH            = "..\\..\\shared\\assets\\";
const string RED_BUFFER_FILENAME   = "redbuffer.jpg";
const string BACK_BUFFER_FILENMAE  = "backbuffer.jpg";
const string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const string WOODS_BITMAP_FILENAME = "Woods.png";
const string FONT_FILENAME         = "cour.ttf";

// Scaling for the steps.
const float WOODS_BITMAP_SCALE = 0.33f;

// Sleep time in seconds.
const double SLEEP_TIME = 5.0;
// Multiplier to change from seconds to milliseconds.
const double SECOND_TO_MILLISECOND = 1000.0;


int main()
{
	Game* game = new Game();

	game->init();

	//Make woods buffer
	GraphicsBuffer* pWoodsBuffer = new GraphicsBuffer(ASSET_PATH, WOODS_BITMAP_FILENAME);

	//Assert Buffers
	assert(pWoodsBuffer);

	//draw woods buffer
	game->draw(pWoodsBuffer);

	//enter the game loop
	game->doLoop();

	// Delete all the pointers to free memory.
	delete game;

	// Make sure the pointers are nulled.
	game = nullptr;


	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}