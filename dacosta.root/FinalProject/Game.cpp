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
#include <string>
#include <cassert>
#include <fstream>

#include "Trackable.h"
#include "Timer.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"
#include "EventTypes.h"
#include "DirectionKeys.h"
#include "UnitTypes.h"

#include "LuaWrapper.hpp"
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
#include "Animation.h"
#include "Level.h"
#include "LevelManager.h"
#include "Unit.h"
#include "Player.h"
#include "UnitManager.h"
#include "GraphicsSystem.h"
#include "System.h"
#include "Game.h"

const std::string CONFIG_FILE = "config.lua";

// Asset locations and names.
//const std::string ASSET_PATH            = "..\\..\\shared\\assets\\";
const std::string COURRIOR_FONT			= "cour.ttf";
//const std::string SPRITE_PATH           = "Sprites\\";
//const std::string WOODS_BUFFER_FILENAME = "Woods.png";
//const std::string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
//const std::string DEAN_SPRITE_FILENAME  = "dean_sprites.png";
//const std::string SNAKE_SPRITE_FILENAME = "Snake.png";
//const std::string WALL_SPRITE_FILENAME  = "Wall.png";
//const std::string FOOD_SPRITE_FILENAME	= "FoodSprite.png";
//const std::string DEAN_SMURF            = "Dean Smurf";
//const std::string SMURF                 = "Smurf";
//const std::string WOODS                 = "Woods";
//const std::string SNAKE_SPRITE          = "Snake";
//const std::string WALL_SPRITE           = "Wall";
//const std::string FOOD_SPRITE           = "Food";

// Spritesheet row and column counts.
//const int SPRITESHEET_ROW_COUNT    = 4;
//const int SPRITESHEET_COLUMN_COUNT = 4;

// Animation speed adjusters.
//const double SPEED_UP = 2.0;
//const double SLOW_DOWN = 0.5;

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

void Game::initialize(int _gridWidth, int _gridHeight, int _cellWidth, int _cellHeight)
{
	LuaScript script("config.lua");
	
	mGridWidth = script.get<int>("grid_width");
	mGridHeight = script.get<int>("grid_height");
	mCellWidth = script.get<int>("cell_width");
	mCellHeight = script.get<int>("cell_height");
	mAssetPath = script.get<std::string>("asset_path");
	mSpritePath = script.get<std::string>("sprite_path");

	// TODO: Move to system.
	int displayWidth =  mGridWidth * mCellWidth;
	int displayHeight = mGridHeight * mCellHeight;

	// Create an easy reference pointer to the event system.
	EventSystem* pEventSystem = EventSystem::getInstance();
	
	// Add all the listeners.
	pEventSystem->addListener(EventType(CREATE_UNIT),           this);
	pEventSystem->addListener(EventType(REMOVE_UNIT),           this);
	pEventSystem->addListener(EventType(TOGGLE_UNIT_ANIMATION), this);
	pEventSystem->addListener(EventType(TOGGLE_UNIT_SPRITE),    this);
	pEventSystem->addListener(EventType(CHANGE_UNIT_DIRECTION), this);
	pEventSystem->addListener(EventType(COLLISION),             this);
	pEventSystem->addListener(EventType(CHANGE_LEVEL),          this);
	pEventSystem->addListener(EventType(EXIT),                  this);

	// Initialize the input translator.
	mpInputTranslator->initialize();

	// Initialize the system.
	mpSystem->initialize(displayWidth, displayHeight);

	// Create a buffer manager.
	mpGraphicsBufferManager = new GraphicsBufferManager;
	
	mSnakeSpriteName = script.get<std::string>("sprites.snake.name");
	mWallSpriteName = script.get<std::string>("sprites.wall.name");
	mFoodSpriteName = script.get<std::string>("sprites.food.name");
	mBlackBufferName = script.get<std::string>("buffers.black.name");
	
	mSpeedUpCollectableName = script.get<std::string>("sprites.speed_up_collectable.name");
	mSlowDownCollectableName = script.get<std::string>("sprites.slow_down_collectable.name");
	mPointsCollectableName = script.get<std::string>("sprites.points_collectable.name");
	
	std::string snake = script.get<std::string>("buffers.snake");
	std::string wall = script.get<std::string>("buffers.wall");
	std::string food = script.get<std::string>("buffers.food");
	std::string speedUp = script.get<std::string>("buffers.speed_up_collectable");
	std::string slowDown = script.get<std::string>("buffers.slow_down_collectable");
	std::string points = script.get<std::string>("buffers.points_collectable");

	mpGraphicsBufferManager->addBuffer(mSnakeSpriteName, new GraphicsBuffer(mSpritePath, snake));

	mpGraphicsBufferManager->addBuffer(mWallSpriteName, new GraphicsBuffer(mSpritePath, wall));

	mpGraphicsBufferManager->addBuffer(mFoodSpriteName, new GraphicsBuffer(mSpritePath, food));

	mpGraphicsBufferManager->addBuffer(mSpeedUpCollectableName, new GraphicsBuffer(mSpritePath, speedUp));

	mpGraphicsBufferManager->addBuffer(mSlowDownCollectableName, new GraphicsBuffer(mSpritePath, slowDown));

	mpGraphicsBufferManager->addBuffer(mPointsCollectableName, new GraphicsBuffer(mSpritePath, points));

	Color bufferColor(script.get<int>("buffers.black.red"), script.get<int>("buffers.black.green"), script.get<int>("buffers.black.blue"));

	mpGraphicsBufferManager->addBuffer(mBlackBufferName, new GraphicsBuffer(displayWidth, displayHeight, bufferColor));

	// Create a unit manager.
	mpUnitManager = new UnitManager;

	mpLevelManager = new LevelManager;


	std::vector<std::string> keys = script.getTableKeys("levels");

	for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		std::string levels = "levels." + *it;

		std::string name = script.get<std::string>(levels + ".name");
		std::vector<int> map = script.getIntVector(levels + ".map");
		int rows = script.get<int>(levels + ".rows");
		int columns = script.get<int>(levels + ".columns");
		int startLength = script.get<int>(levels + ".player.start_length");
		int x = script.get<int>(levels + ".player.x");
		int y = script.get<int>(levels + ".player.y");
		double speed = script.get<double>(levels + ".player.speed");
		int endLength = script.get<int>(levels + ".player.end_length");
		int foodPoints = script.get<int>(levels + ".food_points");
		int powerupFrequency = script.get<int>(levels + ".powerup_frequency");

		createLevel(name, map, rows, columns, startLength, x, y, speed, endLength, foodPoints, powerupFrequency);

	}

	mpLevelManager->setLevel(script.get<std::string>("start_level"));

	addLevelUnits();

	return;
}

// Clean up all the components and end the game.
void Game::cleanUp()
{
	mpLevelManager->cleanUp();

	if (mpLevelManager != nullptr)
	{
		delete mpLevelManager;
	}

	mpLevelManager = nullptr;

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

	//loadLuaFiles();
	
	// Loop the game.
	while (mRunGame)
	{
		// Start the timer.
		pTimer->start();

		// Render the graphics.
		render(waitTime);

		// Update the animation for each unit.
		mpUnitManager->update(waitTime, mpLevelManager);

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
	// TODO: Create black buffer instead.
	//mpSystem->getGraphicsSystem()->draw(*mpGraphicsBufferManager->getBuffer(WOODS));
	//GraphicsBuffer* buffer = mpGraphicsBufferManager->getBuffer(WOODS);
	//mpSystem->getGraphicsSystem()->setBufferColor(*buffer, Color(0, 0, 0));
	//mpSystem->getGraphicsSystem()->draw(*mpGraphicsBufferManager->getBuffer(WOODS));

	// Clear the buffer to black.
	mpSystem->getGraphicsSystem()->draw(*mpGraphicsBufferManager->getBuffer(mBlackBufferName));

	// Draw each unit to the screen.
	mpUnitManager->draw(mpSystem->getGraphicsSystem());

	// Draw the level layout to the screen.
	mpLevelManager->draw(mpSystem->getGraphicsSystem());

	// Draw the HUD to the screen.
	mpLevelManager->drawHUD(mpSystem->getGraphicsSystem(), mScore, Font(mAssetPath, COURRIOR_FONT, 30), Color(255, 255, 255));

	return;
}

// Change the game state to end.
void Game::end()
{
	mRunGame = false;
	return;
}

GraphicsBufferManager* Game::getGraphicsBufferManager()
{
	return mpGraphicsBufferManager;
}

UnitManager* Game::getUnitManager()
{
	return mpUnitManager;
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

			removePlayer(positionX, positionY);

			break;
		}
		case CHANGE_UNIT_DIRECTION:
		{
			ChangeUnitDirectionEvent changeUnitDirectionEvent = dynamic_cast<const ChangeUnitDirectionEvent&>(_theEvent);

			if (!mpLevelManager->getLevel("Main Menu") && !mpLevelManager->getLevel("Game Over"))
			{
				int newDirection = changeUnitDirectionEvent.getDirection();

				changePlayerDirection(newDirection);
			}

			break;
		}
		case TOGGLE_UNIT_ANIMATION:
		{
			toggleAnimation();
			break;
		}
		case TOGGLE_UNIT_SPRITE:
		{
			//toggleSprite();
			switchLevel();
			break;
		}
		case COLLISION:
		{
			CollisionUnitEvent collisionUnitEvent = dynamic_cast<const CollisionUnitEvent&>(_theEvent);

			int type = collisionUnitEvent.getType();

			if (type == FOOD)
			{
				//addPlayerUnit();
				mpUnitManager->updatePlayerSize();
				mScore += mpLevelManager->getLevel()->getFoodPoints();

				if (mpLevelManager->checkPLayerSize(mpUnitManager->getPlayerSize()))
				{
					mpUnitManager->clear();
					switchLevel();
				}
				else
				{
					spawnFood();
					//spawnCollectable();
				}
			}
			else if (type == SPEED_UP_COLLECTABLE)
			{
				/*for (int counter = 0; counter < mpUnitManager->getPlayerSize(); counter++)
				{
					Player* pPlayer = mpUnitManager->getPlayer(counter);
					pPlayer->setSpeed(pPlayer->getSpeed() * 1.1);
				}*/
				break;
			}
			else if (type == SLOW_DOWN_COLLECTABLE)
			{
				/*for (int counter = 0; counter < mpUnitManager->getPlayerSize(); counter++)
				{
					Player* pPlayer = mpUnitManager->getPlayer(counter);
					pPlayer->setSpeed(pPlayer->getSpeed() * 0.9);
				}*/
				break;
			}
			else if (type == POINTS_COLLECTABLE)
			{
				mScore += mpLevelManager->getLevel()->getFoodPoints();
				break;
			}
			else if (type == WALL)
			{
				//mpUnitManager->getPlayer(0)->turnOffMovement();
			}
			else
			{
				gameOver();
			}
			break;
		}
		case CHANGE_LEVEL:
		{
			if (mpLevelManager->getLevel("Main Menu"))
			{
				startGame();
			}
			else if (mpLevelManager->getLevel("Game Over"))
			{
				restartGame();
			}
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
void createSpriteList(GraphicsBuffer* _pSpriteSheet, Sprite* _pSpriteList, int _rowCount, int _columnCount)
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
			_pSpriteList[currentRow * _columnCount + currentColumn] =
				Sprite(_pSpriteSheet, spriteWidth * currentColumn, spriteHeight * currentRow, spriteWidth, spriteHeight);
		}
	}

	return;
}

void Game::createUnit(int _positionX, int _positionY)
{
	//// Create a unit.
	//Unit* pNewUnit = new Unit;

	//// Create a smurf sprite list and add each sprite to the list.
	//Sprite* pSmurfSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
	//createSpriteList(mpGraphicsBufferManager->getBuffer(SMURF), pSmurfSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

	//// Create an animation clip with smurf as the default sprites.
	//Animation* pSmurfAnimation = new Animation;
	//pSmurfAnimation->initialize(pSmurfSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

	//// Set the smurf animation as the default.
	//pNewUnit->setAnimation(pSmurfAnimation);

	//// Add the smurf animation to the animations list.
	//pNewUnit->addAnimation(pSmurfAnimation);

	//// Create a dean sprite list and add each sprite to the list.
	//Sprite* pDeanSprites = new Sprite[SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT];
	//createSpriteList(mpGraphicsBufferManager->getBuffer(DEAN_SMURF), pDeanSprites, SPRITESHEET_ROW_COUNT, SPRITESHEET_COLUMN_COUNT);

	//// Create an animation clip with the dean smurf sprites.
	//Animation* pDeanAnimation = new Animation;
	//pDeanAnimation->initialize(pDeanSprites, SPRITESHEET_ROW_COUNT * SPRITESHEET_COLUMN_COUNT);

	//// Add the dean smurf animation to the animation list.
	//pNewUnit->addAnimation(pDeanAnimation);

	//// Position the unit in the center of the display.
	//pNewUnit->setCenteredPosition(_positionX, _positionY);

	//// Add the new unit to the unit manager.
	//mpUnitManager->addUnit(pNewUnit);
	
	return;
}

void Game::createLevel(LevelKey _key, std::vector<int> _map, int _rows, int _columns, int _playerStartLength, int _playerX, int _playerY, double _playerSpeed, int _playerEndLength, int _foodPoints, int _powerUpFrequency)
{
	Level* pNewLevel = new Level(_map, _rows, _columns, mCellWidth, mCellHeight, _playerStartLength, _playerX, _playerY, _playerSpeed, _playerEndLength, _foodPoints, _powerUpFrequency);
	mpLevelManager->addLevel(_key, pNewLevel);

	return;
}

void Game::createPlayerHead(int _positionX, int _positionY)
{
	// Get the config file.
	LuaScript script(CONFIG_FILE);

	// Create a unit.
	Player* pNewPlayer = new Player;

	int rows = script.get<int>("sprites.snake.row");
	int columns = script.get<int>("sprites.snake.column");

	// Create a sprite.
	Sprite* pNewSprite = new Sprite[rows * columns];
	createSpriteList(mpGraphicsBufferManager->getBuffer(mSnakeSpriteName), pNewSprite, rows, columns);

	// Create an animation clip with.
	Animation* pNewAnimation = new Animation;
	pNewAnimation->initialize(pNewSprite, rows * columns);

	// Set the animation.
	pNewPlayer->setAnimation(pNewAnimation);

	// Add the animation to the animations list.
	pNewPlayer->addAnimation(pNewAnimation);

	// Set the unit position.
	pNewPlayer->setPosition(_positionX, _positionY);

	pNewPlayer->setDirection(WEST);

	pNewPlayer->setQueueDestination(_positionX - 2 * pNewPlayer->getDistance(), _positionY);

	pNewPlayer->setDestination(_positionX - pNewPlayer->getDistance(), _positionY);

	pNewPlayer->setQueueDirection(WEST);

	pNewPlayer->setSpeed(mpLevelManager->getLevel()->getPlayerSpeed());

	// Add the new unit to the unit manager.
	mpUnitManager->addUnit(pNewPlayer);

	mpLevelManager->getLevel()->addPlayerLocation(_positionX, _positionY);

	mpUnitManager->updatePlayerSize();

	//TODO
	// Downcasting parent to child.
	//Player* pPlayer = (Player*) mpUnitManager->getUnit();

	return;
}

void Game::addPlayerUnit()
{
	// Get the config file.
	LuaScript script(CONFIG_FILE);

	// Create a unit.
	Player* pNewPlayer = new Player;

	int rows = script.get<int>("sprites.snake.row");
	int columns = script.get<int>("sprites.snake.column");

	// Create a sprite.
	Sprite* pNewSprite = new Sprite[rows * columns];
	createSpriteList(mpGraphicsBufferManager->getBuffer(mSnakeSpriteName), pNewSprite, rows, columns);

	// Create an animation clip with.
	Animation* pNewAnimation = new Animation;
	pNewAnimation->initialize(pNewSprite, rows * columns);

	// Set the animation.
	pNewPlayer->setAnimation(pNewAnimation);

	// Add the animation to the animations list.
	pNewPlayer->addAnimation(pNewAnimation);

	Player* pLastPlayer = mpUnitManager->getPlayer();

	int direction = pLastPlayer->getDirection();

	// TODO: Get head distance
	int distance = mpUnitManager->getPlayer(0)->getDistance();

	int destinationX = pLastPlayer->getDestinationX();
	int destinationY = pLastPlayer->getDestinationY();

	switch (direction)
	{
		case SOUTH:
			destinationY -= distance;
			break;
		case WEST:
			destinationX += distance;
			break;
		case NORTH:
			destinationY += distance;
			break;
		case EAST:
			destinationX -= distance;
			break;
		default:
			break;
	}

	pNewPlayer->setDestination(destinationX, destinationY);

	pNewPlayer->setQueueDestination(pLastPlayer->getDestinationX(), pLastPlayer->getDestinationY());

	pNewPlayer->setQueueDirection(pLastPlayer->getDirection());
	
	int positionX = pLastPlayer->getPositionX();
	int positionY = pLastPlayer->getPositionY();

	switch (direction)
	{
		case SOUTH:
			positionY -= distance;
			break;
		case WEST:
			positionX += distance;
			break;
		case NORTH:
			positionY += distance;
			break;
		case EAST:
			positionX -= distance;
			break;
		default:
			break;
	}

	// Set the unit position.
	pNewPlayer->setPosition(positionX, positionY);

	pNewPlayer->setDirection(direction);

	pNewPlayer->setSpeed(pLastPlayer->getSpeed());

	// Add the new unit to the unit manager.
	mpUnitManager->addUnit(pNewPlayer);

	// Add the segment to the level.
	mpLevelManager->getLevel()->addPlayerLocation(positionX, positionY);

	mpUnitManager->updatePlayerSize();

	return;
}

//TODO
void Game::removePlayer(int _positionX, int _positionY)
{
	return;
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

void Game::changePlayerDirection(int _direction)
{
	mpUnitManager->setDirection(_direction);

	return;
}

void Game::spawnFood()
{
	LuaScript script("config.lua");

	// Create a unit.
	Unit* pNewFood = new Unit(FOOD);

	int rows = script.get<int>("sprites.food.row");
	int columns = script.get<int>("sprites.food.column");

	// Create a smurf sprite list and add each sprite to the list.
	Sprite* pFoodSprite = new Sprite[rows * columns];
	createSpriteList(mpGraphicsBufferManager->getBuffer(mFoodSpriteName), pFoodSprite, rows, columns);

	// Create an animation clip.
	Animation* pFoodAnimation = new Animation;
	pFoodAnimation->initialize(pFoodSprite, rows * columns, script.get<int>("sprites.food.speed"));

	// Set the smurf animation as the default.
	pNewFood->setAnimation(pFoodAnimation);

	// Add the smurf animation to the animations list.
	pNewFood->addAnimation(pFoodAnimation);

	std::srand(time(NULL));

	// Choose a position on the grid at random.
	int positionX = 0;
	int positionY = 0;

	mpLevelManager->getLevel()->getEmptyLocation(positionX, positionY);

	// Position the unit in the center of the display.
	pNewFood->setPosition(positionX, positionY);

	// Add the new unit to the unit manager.
	mpUnitManager->addUnit(pNewFood);

	return;
}

void Game::spawnCollectable()
{
	std::srand(time(NULL));

	int chance = std::rand() % 100;

	if (chance > mpLevelManager->getLevel()->getPowerUpFrequency())
	{
		return;
	}

	LuaScript script("config.lua");

	int collectable = std::rand() % 3 + SPEED_UP_COLLECTABLE;

	// Create a unit.
	Unit* pNewCollectable = new Unit(collectable);

	int rows = 0;
	int columns = 0;
	std::string name = "";

	switch (collectable)
	{
		case SPEED_UP_COLLECTABLE:
			rows = script.get<int>("sprites.speed_up_collectable.row");
			columns = script.get<int>("sprites.speed_up_collectable.column");
			name = mSpeedUpCollectableName;
			break;
		case SLOW_DOWN_COLLECTABLE:
			rows = script.get<int>("sprites.slow_down_collectable.row");
			columns = script.get<int>("sprites.slow_down_collectable.column");
			name = mSlowDownCollectableName;
			break;
		case POINTS_COLLECTABLE:
			rows = script.get<int>("sprites.points_collectable.row");
			columns = script.get<int>("sprites.points_collectable.column");
			name = mPointsCollectableName;
			break;
		default:
			break;

	}

	// Create a smurf sprite list and add each sprite to the list.
	Sprite* pCollectableSprite = new Sprite[rows * columns];
	createSpriteList(mpGraphicsBufferManager->getBuffer(name), pCollectableSprite, rows, columns);

	// Create an animation clip.
	Animation* pCollectableAnimation = new Animation;
	pCollectableAnimation->initialize(pCollectableSprite, rows * columns, script.get<int>("sprites.food.speed"));

	// Set the smurf animation as the default.
	pNewCollectable->setAnimation(pCollectableAnimation);

	// Add the smurf animation to the animations list.
	pNewCollectable->addAnimation(pCollectableAnimation);

	// Choose a position on the grid at random.
	int positionX = 0;
	int positionY = 0;

	mpLevelManager->getLevel()->getEmptyLocation(positionX, positionY);

	// Position the unit in the center of the display.
	pNewCollectable->setPosition(positionX, positionY);

	// Add the new unit to the unit manager.
	mpUnitManager->addUnit(pNewCollectable);

	return;
}

void Game::switchLevel()
{
	Level* pLevel = mpLevelManager->getLevel();

	mpUnitManager->clear();

	if (!mpLevelManager->getLevel("Main Menu") && !mpLevelManager->getLevel("Game Over"))
	{
		createPlayer(pLevel->getPlayerStartLength(), pLevel->getPlayerStartX(), pLevel->getPlayerStartY());
		//spawnFood();
	}
	
	addLevelUnits();
}

void Game::addLevelUnits()
{
	// Open the config file.
	LuaScript script(CONFIG_FILE);

	Level* pLevel = mpLevelManager->getLevel();

	std::multimap<int, int> walls = pLevel->getWallLocations();

	for (std::multimap<int, int>::iterator iterator = walls.begin(); iterator != walls.end(); iterator++)
	{
		// Create a unit.
		Unit* pNewWall = new Unit(WALL);

		int rows = script.get<int>("sprites.wall.row");
		int columns = script.get<int>("sprites.wall.column");

		// Create a smurf sprite list and add each sprite to the list.
		Sprite* pWallSprite = new Sprite[rows * columns];
		createSpriteList(mpGraphicsBufferManager->getBuffer(mWallSpriteName), pWallSprite, rows, columns);

		// Create an animation clip.
		Animation* pWallAnimation = new Animation;
		pWallAnimation->initialize(pWallSprite, rows * columns);

		// Set the smurf animation as the default.
		pNewWall->setAnimation(pWallAnimation);

		// Add the smurf animation to the animations list.
		pNewWall->addAnimation(pWallAnimation);

		// Position the unit in the center of the display.
		pNewWall->setPosition(iterator->first * mCellWidth, iterator->second * mCellHeight);

		// Add the new unit to the unit manager.
		mpUnitManager->addUnit(pNewWall);
	}
	
	std::multimap<int, int> collectables = pLevel->getCollectableLocations();

	for (std::multimap<int, int>::iterator iterator = collectables.begin(); iterator != collectables.end(); iterator++)
	{
		// Create a unit.
		Unit* pNewCollectable = new Unit(SPEED_UP_COLLECTABLE);

		int rows = script.get<int>("sprites.speed_up_collectable.row");
		int columns = script.get<int>("sprites.speed_up_collectable.column");

		// Create a smurf sprite list and add each sprite to the list.
		Sprite* pCollectableSprite = new Sprite[rows * columns];
		createSpriteList(mpGraphicsBufferManager->getBuffer(mSpeedUpCollectableName), pCollectableSprite, rows, columns);

		// Create an animation clip.
		Animation* pCollectableAnimation = new Animation;
		pCollectableAnimation->initialize(pCollectableSprite, rows * columns);

		// Set the smurf animation as the default.
		pNewCollectable->setAnimation(pCollectableAnimation);

		// Add the smurf animation to the animations list.
		pNewCollectable->addAnimation(pCollectableAnimation);

		// Position the unit in the center of the display.
		pNewCollectable->setPosition(iterator->first * mCellWidth, iterator->second * mCellHeight);

		// Add the new unit to the unit manager.
		mpUnitManager->addUnit(pNewCollectable);
	}
	
	std::multimap<int, int> powerUp = pLevel->getPowerUpLocations();

	for (std::multimap<int, int>::iterator iterator = powerUp.begin(); iterator != powerUp.end(); iterator++)
	{
		// Create a unit.
		Unit* pNewPowerUp = new Unit(SLOW_DOWN_COLLECTABLE);

		int rows = script.get<int>("sprites.slow_down_collectable.row");
		int columns = script.get<int>("sprites.slow_down_collectable.column");

		// Create a smurf sprite list and add each sprite to the list.
		Sprite* pPowerUpSprite = new Sprite[rows * columns];
		createSpriteList(mpGraphicsBufferManager->getBuffer(mSlowDownCollectableName), pPowerUpSprite, rows, columns);

		// Create an animation clip.
		Animation* pPowerUpAnimation = new Animation;
		pPowerUpAnimation->initialize(pPowerUpSprite, rows * columns);

		// Set the smurf animation as the default.
		pNewPowerUp->setAnimation(pPowerUpAnimation);

		// Add the smurf animation to the animations list.
		pNewPowerUp->addAnimation(pPowerUpAnimation);

		// Position the unit in the center of the display.
		pNewPowerUp->setPosition(iterator->first * mCellWidth, iterator->second * mCellHeight);

		// Add the new unit to the unit manager.
		mpUnitManager->addUnit(pNewPowerUp);
	}
}

void Game::createPlayer(int _segmentCount, int _spawnX, int _spawnY)
{
	createPlayerHead(_spawnX, _spawnY);

	for (int counter = 1; counter < _segmentCount; counter++)
	{
		addPlayerUnit();
	}


	return;
}

void Game::startGame()
{
	mpUnitManager->clear();

	mpLevelManager->setLevel("Level 1");

	addLevelUnits();

	Level* pCurrentLevel = mpLevelManager->getLevel();

	createPlayer(pCurrentLevel->getPlayerStartLength(), pCurrentLevel->getPlayerStartX(), pCurrentLevel->getPlayerStartY());

	spawnFood();

	return;
}

void Game::restartGame()
{
	mpUnitManager->clear();

	mScore = 0;

	mpLevelManager->setLevel("Main Menu");

	addLevelUnits();

	return;
}

void Game::gameOver()
{
	mpUnitManager->clear();

	mpLevelManager->setLevel("Game Over");

	addLevelUnits();

	return;
}

//void Game::loadConfig()
//{
//	std::ifstream file;
//
//	file.open(CONFIG_FILE);
//
//	if (file.is_open())
//	{
//
//	}
//	else
//	{
//		std::cout << "Error loading config file." << std::endl;
//	}
//
//	return;
//}

