/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <vector>
#include <map>

#include "Trackable.h"
#include "Timer.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "Unit.h"
#include "UnitManager.h"
#include "GraphicsSystem.h"
#include "System.h"
#include "Game.h"

// Asset locations and names.
const std::string ASSET_PATH            = "..\\..\\shared\\assets\\";
const std::string WOODS_BUFFER_FILENAME = "Woods.png";
const std::string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const std::string DEAN_SPRITE_FILENAME  = "dean_sprites.png";

//buffer keys to find the specified buffer in the buffer manager
const std::string woodsBuffKey = "woodsBuff";
const std::string smurfBuffKey = "smurfBuff";
const std::string deanBuffKey = "deanBuff";

//ints to hold mouse position
int mouseX;
int mouseY;

// Spritesheet row and column counts.
const int SPRITESHEET_ROW_COUNT    = 4;
const int SPRITESHEET_COLUMN_COUNT = 4;

// Animation speed adjusters.
const double SPEED_UP = 2.0;
const double SLOW_DOWN = 0.5;

// Seconds to milliseconds conversion.
const double SECONDS_TO_MILLISECONDS = 1000.0;

//Boolean to stop animation
bool stopAnim = false;

//unit manager
UnitManager* mpUnitManager = new UnitManager;

//Buffer Manager
GraphicsBufferManager* mpGBManager = new GraphicsBufferManager;

// Instantiate a global game object.
Game* gpGame;

// Constructor.
Game::Game()
{
	return;
}

// Destructor.
Game::~Game()
{
	// TODO: Add delete system if added to constructor.
	cleanUp();
	return;
}

void Game::initialize(int _displayWidth, int _displayHeight)
{
	// TODO: Move to constructor. Create system when game is created. Guarantees systems with game.
	// Create a system.
	mpSystem = new System();

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

	//add buffers to buffer manager
	mpGBManager->addBuffToManager(mpWoodsBuffer, woodsBuffKey);
	mpGBManager->addBuffToManager(mpSmurfBuffer, smurfBuffKey);
	mpGBManager->addBuffToManager(mpDeanBuffer, deanBuffKey);

	return;
}

// Clean up all the components and end the game.
void Game::cleanUp()
{
	mpUnitManager->cleanup();

	//delete all the units if its not null
	if (mpUnitManager != nullptr)
	{
		delete mpUnitManager;
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
	
	// Delete the smurf sprites if it isn't null.
	if (mpSmurfSprites != nullptr)
	{
		for (int i = 0; i < 16; i++)
		{
			if(mpSmurfSprites != nullptr)
			{
				delete[] mpSmurfSprites;
				mpSmurfSprites = nullptr;
			}
		}
	}

	mpGBManager->cleanup();

	//if the graphics buffer manager isnt null delete it
	if(mpGBManager != nullptr)
	{
		delete mpGBManager;
	}

	// Delete the system if it isn't null.
	if (mpSystem != nullptr)
	{
		delete mpSystem;
	}

	// Set all the pointers to null to free the memory.
	mpUnit = nullptr;
	mpUnitManager = nullptr; 
	mpAnimation = nullptr; 
	mpDeanSprites = nullptr; 
	mpDeanBuffer = nullptr; 
	mpSmurfSprites = nullptr; 
	mpSmurfBuffer = nullptr; 
	mpWoodsBuffer = nullptr; 
	mpGBManager = nullptr;
	mpSystem = nullptr;

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

		// Draw the woods to the background.
		mpSystem->mpGraphicsSystem->draw(*mpWoodsBuffer);

		// Check the keyboard for input.
		checkKeyState();

		// Check the mouse for input.
		checkMouseState(mpSystem->mpGraphicsSystem);

		// Update the animation.
		if (stopAnim == false)
		{
			mpAnimation->update(waitTime);
			//update animations
			mpUnitManager->update(waitTime);
		}

		//draw everything to the screen
		drawStuff();

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
	//cleanUp();

	return;
}

void Game::drawStuff()
{
	mpSystem->getGraphicsSys()->draw(*mpGBManager->getBuffer(woodsBuffKey));

	mpUnitManager->draw(mpSystem->getGraphicsSys());
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
	// Check if the "Enter" key was pressed to switch the animation.
	if (mpSystem->getKeyState(KEY_ENTER))
	{
		// Make sure the key isn't held down.
		if (!mPressedEnter)
		{
			Unit* swapMe;
			swapMe = mpUnitManager->getUnit();
			if (!mpUnitManager == NULL) 
			{
				if(swapMe != mpUnitManager->getUnit())
				{
					swapMe = mpUnitManager->getUnit();
				}
					
				swapMe->swapAnim();

				// The key has been pressed.
				mPressedEnter = true;
			}
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

	//check if "Space" key was pressed to pause animation
	if (mpSystem->getKeyState(KEY_SPACE))
	{
		if(stopAnim == false)
		{
			stopAnim = true;
		}
		else if(stopAnim = true)
		{
			stopAnim = false;
		}
	}

	return;
}

// Check for mouse input.
void Game::checkMouseState(GraphicsSystem* mSys)
{
	// Check if the left mouse button is pressed.
	if (mpSystem->getMouseState(MOUSE_LEFT))
	{
		// Create temporary mouse coordinates.
		int mouseX = 0;
		int mouseY = 0;

		// Get the current mouse coordinates.
		mpSystem->getMousePosition(mouseX, mouseY);

		//create a new unit
		Unit* addUnit = new Unit;

		// make smurf sprite list
		Sprite* pSmurfSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
		createSpriteList(mpGBManager->getBuffer(smurfBuffKey), pSmurfSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

		// make animation of smurf sprites
		Animation* pSmurfAnimation = new Animation;
		pSmurfAnimation->initialize(pSmurfSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

		//set smurf animation as default
		addUnit->setAnimation(pSmurfAnimation);

		//make list of dean sprites
		Sprite* pDeanSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
		createSpriteList(mpGBManager->getBuffer(deanBuffKey), pDeanSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

		//make animation of dean sprites
		Animation* pDeanAnimation = new Animation;
		pDeanAnimation->initialize(pDeanSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

		//add both animations to the animation vector
		addUnit->addAnimation(pDeanAnimation);
		addUnit->addAnimation(pSmurfAnimation);

		// Position the unit in the center of the display.
		addUnit->setPosition(mouseX, mouseY);

		//add unit to manager
		mpUnitManager->addUnit(addUnit);
	}
	
	if(mpSystem->getMouseState(MOUSE_RIGHT))
	{
		mpSystem->getMousePosition(mouseX, mouseY);
		mpUnitManager->deleteUnit(mouseX, mouseY);
	}
	return;
}