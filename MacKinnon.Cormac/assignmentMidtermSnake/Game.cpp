#include "Game.h"
#include "Event.h"
#include "EventSystem.h"
#include "MouseClickEvent.h"
#include "KeyPressEvent.h"
#include "CreateUnitEvent.h"
#include "DeleteUnitEvent.h"
#include "SwapAnimationEvent.h"
#include "ExitGameEvent.h"
#include "ToggleAnimationActiveEvent.h"
#include "ChangeDirectionEvent.h"
#include "RestartEvent.h"
#include "StartGameEvent.h"

Game* Game::mpsGame = nullptr;
//constructor
Game::Game()
{
	mpSystem = new System();
}

//destructor
Game::~Game()
{
	cleanup();
}

//static class related functions
Game * Game::getInstance()
{
	assert(mpsGame != nullptr);
	return mpsGame;
}

void Game::initInstance()
{
	if (mpsGame == nullptr)
	{
		mpsGame = new Game();
	}
}

void Game::cleanupInstance()
{
	delete mpsGame;
}

//initializes the game and creates the necessary buffers, animations, units, and sprites and creates the display
void Game::init()
{
	mIsInit = true;

	auto eventSystem = EventSystem::getInstance();

	
	eventSystem->addListener(EventType(EXIT_GAME_EVENT), this);
	

	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);

	

	mpInputTranslator = new InputTranslator();
	mpInputTranslator->init();

	LevelManager::initInstance();
	LevelManager::getInstance()->init();

	mpStart = new StartLevel();
	mpStart->init(mpSystem, "Start");
	LevelManager::getInstance()->addLevel("Start", mpStart);

	mpLevel1 = new LevelCreation();
	mpLevel1->init(mpSystem, "Level 1", mLevel1File, ROWS, COLS);
	LevelManager::getInstance()->addLevel("Level 1", mpLevel1);

	mpLevel2 = new LevelCreation();
	mpLevel2->init(mpSystem, "Level 2", mLevel2File, ROWS, COLS);
	LevelManager::getInstance()->addLevel("Level 2", mpLevel2);

	mpLevel3 = new LevelCreation();
	mpLevel3->init(mpSystem, "Level 3", mLevel3File, ROWS, COLS);
	LevelManager::getInstance()->addLevel("Level 3", mpLevel3);

	mpEnd = new EndLevel();
	mpEnd->init(mpSystem, "End");
	LevelManager::getInstance()->addLevel("End", mpEnd);

	
}

//destroys the program properly
void Game::cleanup()
{
	if (!mIsInit)
		return;
	
	LevelManager::cleanupInstance();

	delete mpSystem;
	delete mpInputTranslator;
	

	EventSystem::getInstance()->removeListener((EventType)EXIT_GAME_EVENT, this);

	
	mIsInit = false;
}
//game loop function that keeps track of the frame time
void Game::doLoop()
{
	Timer timer;

	while (!mExitGame)
	{
		timer.start();

		LevelManager::getInstance()->getLevel()->update(FRAME_TIME);

		mpSystem->update(FRAME_TIME);

		//update();
		//render();

		timer.sleepUntilElapsed(FRAME_TIME);
		std::cout << "Frame Time: " << timer.getElapsedTime() << "ms\n";
		LevelManager::getInstance()->getLevel()->drawFrameRate((1000.0 / timer.getElapsedTime()));
		//mpSystem->getGraphicsSystem()->writeText(150, 550, mpGameFont, Color(255, 255, 255), ("FPS: " + to_string(1000.0 / timer.getElapsedTime())));
		timer.stop();
	}
}

//updates the unit
void Game::update()
{	
	/*
	mpSystem->update(FRAME_TIME);

	mpUnitManager->update(FRAME_TIME / 1000.0);

	mpSnakeUnit->update(FRAME_TIME / 1000.0, mGrid);

	collisionCheck();*/
}
//draws all necessary parts onto the back buffer and then flips the screen so they are visible
void Game::render()
{
	/*mpsGame->getSystem()->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(BACKGROUND_BUFFER_KEY), SCALE_FACTOR);

	mpUnitManager->draw();
	mpSnakeUnit->draw(mpSystem, mCellHeight, mCellWidth);
	*/
	//mpSystem->getGraphicsSystem()->flipDisplay();
}
//has the events complete their appropriate action
void Game::handleEvent(const Event& theEvent)
{
	if (EventType(theEvent.getType()) == CREATE_UNIT_EVENT) 
	{
		//auto createUnitEvent = dynamic_cast<const CreateUnitEvent&>(theEvent);
		//mpUnitManager->addUnit(createUnitEvent.getMousePos(), mpSnakeList);
		//mpUnitManager->getUnit()->addAnimation(mpDeanList);
	}
	else if (EventType(theEvent.getType()) == DESTROY_UNIT_EVENT) 
	{
		//auto deleteUnitEvent = dynamic_cast<const DeleteUnitEvent&>(theEvent);
		//mpUnitManager->removeUnits(deleteUnitEvent.getMousePos());
	}
	else if (EventType(theEvent.getType()) == SWAP_ANIMATION_EVENT) 
	{
		//mpUnitManager->getUnit()->setAnimation();
	}
	else if (EventType(theEvent.getType()) == TOGGLE_ANIMATION_ACTIVE_EVENT) 
	{
		//mpUnitManager->toggleAnimationActive();
	}
	else if (EventType(theEvent.getType()) == EXIT_GAME_EVENT) 
	{
		mExitGame = true;
	}
	else if (EventType(theEvent.getType()) == CHANGE_DIRECTION_EVENT) 
	{
		//auto derChangeEvent = dynamic_cast<const ChangeDirectionEvent&>(theEvent);
		//mpSnakeUnit->setDer(derChangeEvent.getX(), derChangeEvent.getY());
	}
	else if (EventType(theEvent.getType()) == START_GAME_EVENT)
	{
		if (mCurrentLevel == 1) //should always be the first scene
		{
			//mpGraphicsBufferManager->removeGraphicsBuffer(START_BUFFER_KEY);
			//mCurrentLevel = 2;
		}
	}
	else if (EventType(theEvent.getType()) == RESTART_EVENT) 
	{
		if (mCurrentLevel == 5) //change 5 if more than 5 scenes
		{
			//mpGraphicsBufferManager->removeGraphicsBuffer(END_BUFFER_KEY);
			//mCurrentLevel = 1;
			//mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + BACKGROUND_IMAGE, START_BUFFER_KEY);
		}
	}
	else if (EventType(theEvent.getType()) == LEVEL_COMPLETE_EVENT) 
	{
		//mCurrentLevel += 1;
	}
}

//accessor
System* Game::getSystem()
{
	return mpSystem;
}
