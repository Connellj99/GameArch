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


/*****************************************************************************************************************************
**													INSTRUCTIONS															**
**																															**
**	[X] Create and initialize GraphicsSystem object 800x600																	**
**	[X] Create 3 GraphicsBuffers (steps, smurfs, red (800x600) from memory)													**
**	[X] Fill red with words "Curse you Papa Smurf!" in black GraphicsSystem::writeText() writes to target graphics buffer	**
**	[X] Draw all red buffer																									**
**	[X] Scale steps buffer by 1/3 and center in red buffer																	**
**	[X] Create 16 smurf sprites (1 each from spritesheet) at random locations												**
**	[X] Save the Back Buffer to backbuffer.jpg using GraphicsSystem::saveBuffer()											**
**	[X] Save the RedBuffer with text to redbuffer.jpg using GraphicsSystem::saveBuffer()									**
**	[X] Flip the display																									**
**	[X] Close display gracefully after 5 seconds																			**
*****************************************************************************************************************************/

// Display dimensions.
const int DISPLAY_WIDTH  = 800;
const int DISPLAY_HEIGHT = 600;

// Asset locations and names.
const std::string ASSET_PATH            = "..\\..\\shared\\assets\\";
const std::string RED_BUFFER_FILENAME   = "redbuffer.jpg";
const std::string BACK_BUFFER_FILENMAE  = "backbuffer.jpg";
const std::string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const std::string STEPS_BITMAP_FILENAME = "steps.png";
const std::string FONT_FILENAME         = "cour.ttf";

// Printed text.
const std::string SMURF_MESSAGE = "Curse you Papa Smurf!";

// Font size.
const int FONT_SIZE = 40;

// Spritesheet row and column counts.
const int SPRITESHEET_ROW_COUNT    = 4;
const int SPRITESHEET_COLUMN_COUNT = 4;

// Write text coordinates.
const float TEXT_X = 50;
const float TEXT_Y = 50;

// Scaling for the steps.
const float STEPS_BITMAP_SCALE = 0.33f;

// Text and background colors.
const Color RED_COLOR   = Color(255, 0, 0);
const Color BLACK_COLOR = Color(0,   0, 0);

// Sleep time in seconds.
const double SLEEP_TIME = 5.0;
// Multiplier to change from seconds to milliseconds.
const double SECOND_TO_MILLISECOND = 1000.0;


int main()
{
	// Create a random seed for number generation.
	srand(time(NULL));

	// Create a performance tracker.
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	/*********************
		Tracker names.
	**********************/
	const std::string INIT_TRACKER_NAME = "init";
	const std::string DRAW_TRACKER_NAME = "draw";
	const std::string WAIT_TRACKER_NAME = "wait";

	// Start tracking the initialization.
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	// Create graphics system.
	GraphicsSystem* pGraphicsSystem = new GraphicsSystem();

	// Initalize the graphics system with a given dimension.
	pGraphicsSystem->initialize(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// Stop tracking initialization.
	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);

	// Start tracking drawing.
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);

	// Create steps graphics buffer.
	GraphicsBuffer* pStepsBuffer = new GraphicsBuffer(ASSET_PATH, STEPS_BITMAP_FILENAME);

	// Assert buffers. Assertions check it gets made. Don't use in build.
	assert(pStepsBuffer && pSmurfsBuffer && pRedBuffer);

	// Set the given buffer to a given color..
	pGraphicsSystem->setBufferColor(*pRedBuffer, RED_COLOR);

	// Create a new font.
	Font* pCourrierFont = new Font(ASSET_PATH, FONT_FILENAME, FONT_SIZE);
	
	// Draw text to the red buffer in black "Curse you Papa Smurf!".
	pGraphicsSystem->writeText(*pRedBuffer, TEXT_X, TEXT_Y, *pCourrierFont, BLACK_COLOR, SMURF_MESSAGE);

	// Save the red buffer to redbuffer.jpg.
	pGraphicsSystem->saveBuffer(*pRedBuffer, RED_BUFFER_FILENAME);

	// Draw the steps buffer on the red buffer scaled by 1/3.
	pGraphicsSystem->draw(*pStepsBuffer, *pRedBuffer, BUFFER_CENTER, STEPS_BITMAP_SCALE);

	// Draw the red buffer directly to the back buffer.
	pGraphicsSystem->draw(*pRedBuffer);

	

	// Calculate the sprite width.
	int spriteWidth = pSmurfsBuffer->getWidth() / SPRITESHEET_COLUMN_COUNT;

	// Calculate the sprite height.
	int spriteHeight = pSmurfsBuffer->getHeight() / SPRITESHEET_ROW_COUNT;

	// Create a separate sprite for each one on the sheet and add it to an array.
	for (int spriteRow = 0; spriteRow < SPRITESHEET_COLUMN_COUNT; spriteRow++)
	{
		for (int spriteColumn = 0; spriteColumn < SPRITESHEET_COLUMN_COUNT; spriteColumn++)
		{
			smurfSprites[spriteRow * SPRITESHEET_ROW_COUNT + spriteColumn] = Sprite(pSmurfsBuffer, spriteWidth * spriteColumn, spriteHeight * spriteRow, spriteWidth, spriteHeight);
		}
	}

	// Randomly draw each sprite on the buffer.
	for (int currentSprite = 0; currentSprite < SPRITESHEET_COLUMN_COUNT * SPRITESHEET_ROW_COUNT; currentSprite++)
	{
		// Calculate a random horizontal point within the buffer.
		float destinationX = rand() % (pGraphicsSystem->getWidth() - spriteWidth) + 1;
		// Calculate a vertical point within the buffer.
		float destinationY = rand() % (pGraphicsSystem->getHeight() - spriteHeight) + 1;

	// Save the back buffer to backbuffer.jpg.
	pGraphicsSystem->saveBuffer(pGraphicsSystem->getBackBuffer(), BACK_BUFFER_FILENMAE);

	// Update the display.
	pGraphicsSystem->updateDisplay();

	// Stop tracking drawing.
	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);

	// Start tracking waiting.
	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);

	/******************
		Wait timer.
	*******************/
	Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(SLEEP_TIME * SECOND_TO_MILLISECOND);

	// Stop tracking waiting.
	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);

	/****************************
		Report elapsed times.
	*****************************/
	std::cout << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << std::endl;
	std::cout << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << std::endl;
	std::cout << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << std::endl;

	// Delete all the pointers to free memory.
	delete pTimer;
	delete pPerformanceTracker;
	delete pGraphicsSystem;
	delete pRedBuffer;
	delete pSmurfsBuffer;
	delete pStepsBuffer;
	delete pCourrierFont;

	// Make sure the pointers are nulled.
	pTimer = nullptr;
	pPerformanceTracker = nullptr;
	pGraphicsSystem = nullptr;
	pRedBuffer = nullptr;
	pStepsBuffer = nullptr;
	pSmurfsBuffer = nullptr;
	pCourrierFont = nullptr;

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}