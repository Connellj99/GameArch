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




// Display dimensions.
const int DISPLAY_WIDTH = 800;
const int DISPLAY_HEIGHT = 600;

// Asset locations and names.
const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
//const std::string RED_BUFFER_FILENAME = "redbuffer.jpg";
//const std::string BACK_BUFFER_FILENAME = "backbuffer.jpg";
const std::string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const std::string DEAN_SPRITE_FILENAME = "dean_sprites.png";
//const std::string STEPS_BITMAP_FILENAME = "steps.png";
const std::string WOODS_BITMAP_FILENAME = "woods.png";
const std::string FONT_FILENAME = "cour.ttf";

// Printed text.
//const std::string SMURF_MESSAGE = "Curse you Papa Smurf!";

// Font size.
const int FONT_SIZE = 40;

// Spritesheet row and column counts.
const int SPRITESHEET_ROW_COUNT = 4;
const int SPRITESHEET_COLUMN_COUNT = 4;

// Write text coordinates.
const float TEXT_X = 50;
const float TEXT_Y = 50;

// Scaling for the steps.
const float STEPS_BITMAP_SCALE = 0.33f;

// Text and background colors.
const Color RED_COLOR = Color(255, 0, 0);
const Color BLACK_COLOR = Color(0, 0, 0);

// Sleep time in seconds.
const double SLEEP_TIME = 5.0;


int main()
{
	// Create a random seed for number generation.
	srand(time(NULL));

	// Create a performance tracker.
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	//tracker names
	const std::string INIT_TRACKER_NAME = "init";
	const std::string DRAW_TRACKER_NAME = "draw";
	const std::string WAIT_TRACKER_NAME = "wait";

	// Start tracking the initialization.
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	// Create graphics system with 800x600 display.
	GraphicsSystem graphicsSystem = GraphicsSystem();

	// Initalize the graphics system.
	graphicsSystem.initialize(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// Stop tracking initialization.
	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);

	// Start tracking drawing.
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);

	// Create woods graphics buffer.
	GraphicsBuffer woodsBuffer = GraphicsBuffer(ASSET_PATH, WOODS_BITMAP_FILENAME);

	// Create smurfs graphics buffer.
	GraphicsBuffer smurfsBuffer = GraphicsBuffer(ASSET_PATH, SMURF_SPRITE_FILENAME);

	// Create dean smurfs graphics buffer.
	GraphicsBuffer deansBuffer = GraphicsBuffer(ASSET_PATH, DEAN_SPRITE_FILENAME);

	// Create red graphics buffer.
	//GraphicsBuffer redBuffer = GraphicsBuffer(DISPLAY_WIDTH, DISPLAY_HEIGHT, RED_COLOR);

	// Create a new font.
	Font courrierFont = Font(ASSET_PATH, FONT_FILENAME, FONT_SIZE);

	// Draw text to the red buffer in black "Curse you Papa Smurf!".
	//graphicsSystem.writeText(redBuffer, TEXT_X, TEXT_Y, courrierFont, BLACK_COLOR, SMURF_MESSAGE);

	// Save the red buffer to redbuffer.jpg.
	//graphicsSystem.saveBuffer(redBuffer, RED_BUFFER_FILENAME);

	// Draw the red buffer.
	//graphicsSystem.draw(redBuffer);

	// TODO: Include target buffer to draw to. Don't draw directly to back buffer.
	// Draw the steps buffer on the red buffer scaled by 1/3.
	graphicsSystem.draw(woodsBuffer, STEPS_BITMAP_SCALE);

	// Create an array to store each sprite.
	Sprite smurfSprites[SPRITESHEET_COLUMN_COUNT * SPRITESHEET_ROW_COUNT];

	Sprite deanSprites[SPRITESHEET_COLUMN_COUNT * SPRITESHEET_ROW_COUNT];

	// Calculate the sprite width.
	int smurfWidth = smurfsBuffer.getWidth() / SPRITESHEET_COLUMN_COUNT;

	// Calculate the sprite height.
	int smurfHeight = smurfsBuffer.getHeight() / SPRITESHEET_ROW_COUNT;

	// Calculate the sprite width.
	int deanWidth = deansBuffer.getWidth() / SPRITESHEET_COLUMN_COUNT;

	// Calculate the sprite height.
	int deanHeight = deansBuffer.getHeight() / SPRITESHEET_ROW_COUNT;

	// Create a separate sprite for each one on the sheet and add it to an array.
	for (int spriteRow = 0; spriteRow < SPRITESHEET_COLUMN_COUNT; spriteRow++)
	{
		for (int spriteColumn = 0; spriteColumn < SPRITESHEET_COLUMN_COUNT; spriteColumn++)
		{
			smurfSprites[spriteRow * SPRITESHEET_ROW_COUNT + spriteColumn] = Sprite(&smurfsBuffer, smurfWidth * spriteColumn, smurfHeight * spriteRow, smurfWidth, smurfHeight);
		}
	}

	for (int spriteRow = 0; spriteRow < SPRITESHEET_COLUMN_COUNT; spriteRow++)
	{
		for (int spriteColumn = 0; spriteColumn < SPRITESHEET_COLUMN_COUNT; spriteColumn++)
		{
			deanSprites[spriteRow * SPRITESHEET_ROW_COUNT + spriteColumn] = Sprite(&smurfsBuffer, deanWidth * spriteColumn, deanHeight * spriteRow, deanWidth, deanHeight);
		}
	}

	// Randomly draw each sprite on the buffer.
	//for (int currentSprite = 0; currentSprite < SPRITESHEET_COLUMN_COUNT * SPRITESHEET_ROW_COUNT; currentSprite++)
	//{
	//	// Calculate a random horizontal point within the buffer.
	//	float destinationX = rand() % (graphicsSystem.getWidth() - spriteWidth) + 1;
	//	// Calculate a vertical point within the buffer.
	//	float destinationY = rand() % (graphicsSystem.getHeight() - spriteHeight) + 1;

	//	// Draw the sprite on the buffer.
	//	graphicsSystem.draw(smurfSprites[currentSprite], destinationX, destinationY);
	//}


	// Save the back buffer to backbuffer.jpg.
	//graphicsSystem.saveBuffer(graphicsSystem.getBackBuffer(), BACK_BUFFER_FILENMAE);

	// Update the display.
	graphicsSystem.updateDisplay();

	// Stop tracking drawing.
	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);

	// Start tracking waiting.
	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);

	//wait timer
	Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(SLEEP_TIME*1000.0);

	//game timer--goes into game classs
	bool keepGoing = true;
	Timer* theTimer = new Timer;
	while (keepGoing)
	{
		pPerformanceTracker->clearTracker("loop");
		pPerformanceTracker->startTracking("loop");
		//get current time
		//do all loop processing
		//get  current time 2
		//elapsed time = time2 - time;
		//time to sleep = target time - elapsed time
		//sleep for time to sleep
		//timer start does all of the above
		theTimer->start();
		//do all loop processing

		//unit.update(pass in deltaTime (dt) which is time2-time(basically just 16.7)); //in game loop to update the unit

		//16.7 is 60fps
		theTimer->sleepUntilElapsed(16.7);
		pPerformanceTracker->stopTracking("loop");
		std::cout << "Time spent waiting:" << pPerformanceTracker->getElapsedTime("loop") << " ms" << std::endl;

	}

	// Stop tracking waiting.
	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);

	// TODO: Move the GraphicsSystem destructor.
	// NOTE: Not working from destructor because graphicsSystem doesn't go out of scope. Change graphicsSystem to a pointer?
	// Clean up the system.
	graphicsSystem.cleanUp();

	//report elapsed time
	std::cout << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << std::endl;
	std::cout << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << std::endl;
	std::cout << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << std::endl;

	// Delete pTimer and pPerformanceTracker to free up memory.
	delete pTimer;
	delete pPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}
/*
void update()//animation update example call double dt in update to acquire delta time (which is 16.7)
{
	double targetTime = 100;
	double timeBetweenFrames = targetTime;

	double dt = 16.7;

	timeBetweenFrames -= dt;
	//if timebetwenframes <= 0)
	//change animation sprite
	//to go slow, decrease target time
	//to go fast, increase target time
	//reset after, timeBetweenFrames = targetTime

}*/

//key stuff
/*
enum Keys
{
	F = ALLEGRO_KEY_F, 
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	ESC = ALLEGRO_KEY_ESCAPE

};
*/