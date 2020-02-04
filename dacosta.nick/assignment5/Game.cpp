/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <assert.h>
#include <vector>
#include <map>

#include "Trackable.h"
#include "Timer.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"
#include "EventTypes.h"

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
const std::string DEAN_SMURF            = "Dean Smurf";
const std::string SMURF                 = "Smurf";
const std::string WOODS                 = "Woods";     

// Spritesheet row and column counts.
const int SPRITESHEET_ROW_COUNT    = 4;
const int SPRITESHEET_COLUMN_COUNT = 4;

// Animation speed adjusters.
const double SPEED_UP = 2.0;
const double SLOW_DOWN = 0.5;

// Seconds to milliseconds conversion.
const double SECONDS_TO_MILLISECONDS = 1000.0;

Game* Game::smpInstance = nullptr;

// Get the instance.
Game* Game::getInstance()
{
	// Make sure the instance exists first.
	assert(smpInstance != nullptr);

	// Return the instance.
	return smpInstance;
}

// Initialize the instance.
void Game::initializeInstance()
{
	// Create a new instance of game if it doesn't exist.
	if (smpInstance == nullptr)
	{
		smpInstance = new Game;
	}

	return;
}

// Clean up the instance.
void Game::cleanUpInstance()
{
	delete smpInstance;
	smpInstance = nullptr;
	return;
}

void Game::initialize(int _displayWidth, int _displayHeight)
{
	// Create an easy reference pointer to the event system.
	EventSystem* pEventSystem = EventSystem::getInstance();
	
	// Add all the listeners.
	pEventSystem->addListener(EventType(CREATE_UNIT),           this); 
	pEventSystem->addListener(EventType(REMOVE_UNIT),           this); 
	pEventSystem->addListener(EventType(TOGGLE_UNIT_ANIMATION), this); 
	pEventSystem->addListener(EventType(TOGGLE_UNIT_SPRITE),    this); 
	pEventSystem->addListener(EventType(EXIT),				    this);

	// Initialize the input translator.
	mpInputTranslator->initialize();

	// Initialize the system.
	mpSystem->initialize(_displayWidth, _displayHeight);

	// Create a buffer manager.
	mpGraphicsBufferManager = new GraphicsBufferManager;

	// Create a woods buffer initialize it and add it to the buffer manager.
	mpGraphicsBufferManager->addBuffer(WOODS, new GraphicsBuffer(ASSET_PATH, WOODS_BUFFER_FILENAME));
	
	// Create a smurf buffer and initialize it and add it to the buffer manager.
	mpGraphicsBufferManager->addBuffer(SMURF, new GraphicsBuffer(ASSET_PATH, SMURF_SPRITE_FILENAME));
			
	// Create a dean buffer and initialize it.
	mpGraphicsBufferManager->addBuffer(DEAN_SMURF, new GraphicsBuffer(ASSET_PATH, DEAN_SPRITE_FILENAME));

	// Create a unit manager.
	mpUnitManager = new UnitManager;

	return;
}

// Clean up all the components and end the game.
void Game::cleanUp()
{	
	// Clean the unit manager.
	mpUnitManager->cleanUp();

	// Delete the unit manager if it isn't null.
	if (mpUnitManager != nullptr)
	{
		delete mpUnitManager;
	}

	// Set the pointer to null to free the memory.
	mpUnitManager  = nullptr;

	// Clean the graphics buffer manager.
	mpGraphicsBufferManager->cleanUp();

	// Delete the graphics buffer manager is it isn't null.
	if (mpGraphicsBufferManager != nullptr)
	{
		delete mpGraphicsBufferManager;
	}

	// Set the pointer to null to free memory.
	mpGraphicsBufferManager = nullptr;

	mpInputTranslator->cleanUp();

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

		// Update the animation for each unit.
		mpUnitManager->update(waitTime);

		// Render the graphics.
		render(waitTime);

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

	return;
}

// Render all the graphics.
void Game::render(double _deltaTime)
{
	// Draw the woods to the background.
	mpSystem->getGraphicsSystem()->draw(*mpGraphicsBufferManager->getBuffer(WOODS));

	// Draw each unit to the screen.
	mpUnitManager->draw(mpSystem->getGraphicsSystem());

	return;
}

// Change the game state to end.
void Game::end()
{
	mRunGame = false;
	return;
}

void Game::handleEvent(const Event& _theEvent)
{
	
	switch (GameEventType(_theEvent.getType()))
	{
		case CREATE_UNIT:
		{
			CreateUnitEvent createUnitEvent = dynamic_cast<const CreateUnitEvent&>(_theEvent);

			int positionX = 0;
			int positionY = 0;

			createUnitEvent.getPosition(positionX, positionY);

			createUnit(positionX, positionY);

			break;
		}
		case REMOVE_UNIT:
		{
			RemoveUnitEvent removeUnitEvent = dynamic_cast<const RemoveUnitEvent&>(_theEvent);

			int positionX = 0;
			int positionY = 0;

			removeUnitEvent.getPosition(positionX, positionY);

			removeUnit(positionX, positionY);

			break;
		}
		case TOGGLE_UNIT_ANIMATION:
		{
			toggleAnimation();
			break;
		}
		case TOGGLE_UNIT_SPRITE:
		{
			toggleSprite();
			break;
		}
		case EXIT:
		{
			end();
			break;
		}
		default:
			break;
	}
	return;
}

// Constructor.
Game::Game()
{
	// Make sure a system is made with every game.
	mpSystem = new System;
	mpInputTranslator = new InputTranslator;
	
	return;
}

// Destructor.
Game::~Game()
{
	// Clean this instance.
	cleanUp();

	// Delete the input translator if it exists.
	if (mpInputTranslator != nullptr)
	{
		delete mpInputTranslator;
	}

	// Delete the system if it exists.
	if (mpSystem != nullptr)
	{
		delete mpSystem;
	}

	// Clear the memory allocation.
	mpSystem = nullptr;
	mpInputTranslator = nullptr;
	
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

void Game::createUnit(int _positionX, int _positionY)
{
	// Create a unit.
	Unit* pNewUnit = new Unit;

	// Create a smurf sprite list and add each sprite to the list.
	Sprite* pSmurfSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
	createSpriteList(mpGraphicsBufferManager->getBuffer(SMURF), pSmurfSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

	// Create an animation clip with smurf as the default sprites.
	Animation* pSmurfAnimation = new Animation;
	pSmurfAnimation->initialize(pSmurfSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

	// Set the smurf animation as the default.
	pNewUnit->setAnimation(pSmurfAnimation);

	// Add the smurf animation to the animations list.
	pNewUnit->addAnimation(pSmurfAnimation);

	// Create a dean sprite list and add each sprite to the list.
	Sprite* pDeanSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
	createSpriteList(mpGraphicsBufferManager->getBuffer(DEAN_SMURF), pDeanSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

	// Create an animation clip with the dean smurf sprites.
	Animation* pDeanAnimation = new Animation;
	pDeanAnimation->initialize(pDeanSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

	// Add the dean smurf animation to the animation list.
	pNewUnit->addAnimation(pDeanAnimation);

	// Position the unit in the center of the display.
	pNewUnit->setPosition(_positionX, _positionY);

	// Add the new unit to the unit manager.
	mpUnitManager->addUnit(pNewUnit);

	return;
}

void Game::removeUnit(int _positionX, int _positionY)
{
	// Delete the last added unit if it is colliding with the mouse.
	mpUnitManager->deleteUnit(_positionX, _positionY);
}

void Game::toggleAnimation()
{
	// Toggle all the units' animation on/off.
	mpUnitManager->toggleAnimation();
}

void Game::toggleSprite()
{
	// Get the last unit.
	Unit* pLastUnit = mpUnitManager->getUnit();

	// Change the last unit's animation if it isn't null.
	if (pLastUnit != nullptr)
	{
		pLastUnit->switchAnimation();
	}
}
