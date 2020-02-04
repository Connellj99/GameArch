/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"
#include "Timer.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "Unit.h"
#include "GraphicsSystem.h"
#include "System.h"
#include "Game.h"

// Asset locations and names.
const std::string ASSET_PATH            = "..\\..\\shared\\assets\\";
const std::string WOODS_BUFFER_FILENAME = "Woods.png";
const std::string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const std::string DEAN_SPRITE_FILENAME  = "dean_sprites.png";

// Spritesheet row and column counts.
const int SPRITESHEET_ROW_COUNT    = 4;
const int SPRITESHEET_COLUMN_COUNT = 4;

// Animation speed adjusters.
const double SPEED_UP = 2.0;
const double SLOW_DOWN = 0.5;

// Seconds to milliseconds conversion.
const double SECONDS_TO_MILLISECONDS = 1000.0;

// Instantiate a global game object.
Game* gpGame;

// Constructor.
Game::Game()
{
	// Make sure a system is made with every game.
	mpSystem = new System();

	return;
}

// Destructor.
Game::~Game()
{
	// Clean this instance.
	cleanUp();

	// Delete the system if it exists.
	if (mpSystem != nullptr)
	{
		delete mpSystem;
	}

	// Clear the memory allocation.
	mpSystem = nullptr;

	return;
}

void Game::initialize(int _displayWidth, int _displayHeight)
{
	// Initialize the system.
	mpSystem->initialize(_displayWidth, _displayHeight);
	
	// Create a woods buffer and initialize it.
	mpWoodsBuffer = new GraphicsBuffer(ASSET_PATH, WOODS_BUFFER_FILENAME);
	
	// Create a smurf buffer and initialize it.
	mpSmurfBuffer = new GraphicsBuffer(ASSET_PATH, SMURF_SPRITE_FILENAME);

	// Create a smurf sprite list and add each sprite to the list.
	mpSmurfSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
	createSpriteList(mpSmurfBuffer, mpSmurfSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);
		
	// Create a dean buffer and initialize it.
	mpDeanBuffer = new GraphicsBuffer(ASSET_PATH, DEAN_SPRITE_FILENAME);

	// Create a dean sprite list and add each sprite to the list.
	mpDeanSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
	createSpriteList(mpDeanBuffer, mpDeanSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

	// Create an animation clip with smurf as the default sprite.
	mpAnimation = new Animation();
	mpAnimation->initialize(mpSmurfSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

	// Create a unit.
	mpUnit = new Unit();

	// Set the animation for the unit.
	mpUnit->setAnimation(mpAnimation);

	// Position the unit in the center of the display.
	mpUnit->setPosition(_displayWidth / 2, _displayHeight / 2);

	return;
}

// Clean up all the components and end the game.
void Game::cleanUp()
{
	// Delete the unit if it isn't null.
	if (mpUnit != nullptr)
	{
		delete mpUnit;
	}
	
	// Delete the animation if it isn't null.
	if (mpAnimation != nullptr)
	{
		delete mpAnimation;
	}
	
	// Delete the dean sprites if it isn't null.
	if (mpDeanSprites != nullptr)
	{
		delete[] mpDeanSprites;
	}
	
	// Delete the dean buffer if it isn't null.
	if (mpDeanBuffer != nullptr)
	{
		delete mpDeanBuffer;
	}
	
	// Delete the smurf sprites if it isn't null.
	if (mpSmurfSprites != nullptr)
	{
		delete[] mpSmurfSprites;
	}
	
	// Delete the smurf buffer if it isn't null.
	if (mpSmurfBuffer != nullptr)
	{
		delete mpSmurfBuffer;
	}
	
	// Delete the woods buffer if it isn't null.
	if (mpWoodsBuffer != nullptr)
	{
		delete mpWoodsBuffer;
	}

	// Set all the pointers to null to free the memory.
	mpUnit         = nullptr;
	mpAnimation    = nullptr;
	mpDeanSprites  = nullptr;
	mpDeanBuffer   = nullptr;
	mpSmurfSprites = nullptr;
	mpSmurfBuffer  = nullptr;
	mpWoodsBuffer  = nullptr;

	return;
}

// The main game loop.
void Game::loop(double _framesPerSecond)
{
	// Create a timer to keep track of frame rates.
	Timer* pTimer = new Timer;

	// Calculate the frame rate waiting period.
	double waitTime = SECONDS_TO_MILLISECONDS / _framesPerSecond;
	
	// Loop the game.
	while (mRunGame)
	{
		// Start the timer.
		pTimer->start();
		
		// Check the keyboard for input.
		checkKeyState();

		// Check the mouse for input.
		checkMouseState();

		// Update the animation.
		mpAnimation->update(waitTime);

		// Render the graphics.
		render();

		// Update the system.
		mpSystem->update();
		 
		// Sleep the remainder of the loop based on the calculated frame rate.
		pTimer->sleepUntilElapsed(waitTime);

		// Print the elapsed time to the screen.
		std::cout << "Elapsed time: " << pTimer->getElapsedTime() << std::endl;

		// Stop the timer so it can reset.
		pTimer->stop();
	}

	// Delete the timer and make it null.
	delete pTimer;
	pTimer = nullptr;

	// Clean up the game object.
	cleanUp();

	return;
}

// Render all the graphics.
void Game::render()
{
	// Draw the woods to the background.
	mpSystem->getGraphicsSystem()->draw(*mpWoodsBuffer);

	// Draw the unit to the display.
	mpUnit->draw(mpSystem->getGraphicsSystem());

	return;
}

// Change the game state to end.
void Game::end()
{
	mRunGame = false;
	return;
}

// Separate each sprite from its buffer.
void Game::createSpriteList(GraphicsBuffer* _pSpriteSheet, Sprite* _pSpriteList, int _rowCount, int _columnCount)
{
	// Calculate the width of each sprite.
	int spriteWidth = _pSpriteSheet->getWidth() / _columnCount;

	// Calculate the height of each sprite.
	int spriteHeight = _pSpriteSheet->getHeight() / _rowCount;

	// Add each sprite to the list.
	for (int currentRow = 0; currentRow < _rowCount; currentRow++)
	{
		for (int currentColumn = 0; currentColumn < _columnCount; currentColumn++)
		{
			_pSpriteList[currentRow * _rowCount + currentColumn] =
				Sprite(_pSpriteSheet, spriteWidth * currentColumn, spriteHeight * currentRow, spriteWidth, spriteHeight);
		}
	}

	return;
}

// Check for keyboard input.
void Game::checkKeyState()
{
	// Check if the "S" key was pressed to slow down animation.
	if (mpSystem->getKeyState(KEY_S))
	{
		// Make sure the key isn't held down.
		if (!mPressedS)
		{
			// Change the animation speed.
			mpAnimation->adjustSpeed(SLOW_DOWN);

			// The key has been pressed.
			mPressedS = true;
		}
	}
	else
	{
		// The key has been released.
		mPressedS = false;
	}

	// Check if the "F" key was pressed to speed up animation.
	if (mpSystem->getKeyState(KEY_F))
	{
		// Make sure the key isn't held down.
		if (!mPressedF)
		{
			// Change the animation speed.
			mpAnimation->adjustSpeed(SPEED_UP);

			// The key has been pressed.
			mPressedF = true;
		}
	}
	else
	{
		// The key has been released.
		mPressedF = false;
	}

	// Check if the "Enter" key was pressed to switch the animation.
	if (mpSystem->getKeyState(KEY_ENTER))
	{
		// Make sure the key isn't help down.
		if (!mPressedEnter)
		{
			// Change the animation clip based on the current one.
			if (mpAnimation->getCurrentClip() == mpDeanSprites)
			{
				// Set the animation to the smurfs.
				mpAnimation->setAnimationClip(mpSmurfSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);
			}
			else
			{
				// Set the animation to dean.
				mpAnimation->setAnimationClip(mpDeanSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);
			}

			// The key has been pressed.
			mPressedEnter = true;
		}
	}
	else
	{
		// The key has been release.
		mPressedEnter = false;
	}

	// Check if the "Escape" key was pressed to exit the game.
	if (mpSystem->getKeyState(KEY_ESCAPE))
	{
		// Change the game state to end.
		end();
	}

	return;
}

// Check for mouse input.
void Game::checkMouseState()
{
	// Check if the left mouse button is pressed.
	if (mpSystem->getMouseState(MOUSE_LEFT))
	{
		// Create temporary mouse coordinates.
		int mouseX = 0;
		int mouseY = 0;

		// Get the current mouse coordinates.
		mpSystem->getMousePosition(mouseX, mouseY);

		// Set the position of the unit to the mouse.
		mpUnit->setPosition(mouseX, mouseY);
	}
	return;
}