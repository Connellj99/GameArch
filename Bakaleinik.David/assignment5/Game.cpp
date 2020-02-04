#include "Game.h"
#include "Unit.h"
#include "System.h"
#include "Timer.h"
#include "GraphicsBuffer.h"
#include "PerformanceTracker.h"
#include "Animation.h"
#include "GBufferManager.h"
#include "UnitManager.h"
#include "InputSystem.h"
#include "EventSystem.h"
#include "Event.h" //May be not needed
#include "GameEvent.h"
#include "CreateUnit.h"
#include "DeleteUnit.h"
#include "ExitGame.h"
#include "SwitchHead.h"
#include "StopAnim.h"


Game * Game::mpGameInstance = nullptr;

const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string DEANS = "dean_sprites.png";
const string SMURFS = "smurf_sprites.png";

using namespace std;

Game* gpGame = nullptr;

Game::Game(EventSystem* pEventSystem) 
	:EventListener(pEventSystem)
{
	
	pEventSystem->addListener((EventType)STOP_ANIMATION, this);
	pEventSystem->addListener((EventType)HEAD_SWITCH, this);
	pEventSystem->addListener((EventType)CREATE_UNIT, this);
	pEventSystem->addListener((EventType)DELETE_UNIT, this);
	pEventSystem->addListener((EventType)EXIT_GAME, this);



}

Game::Game(double fps, EventSystem* pEventSystem)		
	:EventListener(pEventSystem)
{
	mTargetTime = fps;
	pEventSystem->addListener((EventType)STOP_ANIMATION, this);
	pEventSystem->addListener((EventType)HEAD_SWITCH, this);
	pEventSystem->addListener((EventType)CREATE_UNIT, this);
	pEventSystem->addListener((EventType)DELETE_UNIT, this);
	pEventSystem->addListener((EventType)EXIT_GAME, this);
}

Game::~Game()
{

}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == STOP_ANIMATION) 
	{
		//Stop Animation
		mpUnitManager->disableAnimation();
		

	}
	else if (theEvent.getType() == HEAD_SWITCH)
	{
		//Change heads
		mpUnitManager->switchHead(mpDeanSmurf, mpNormalSmurf);
	}
	else if (theEvent.getType() == EXIT_GAME)
	{
		//Exit the game loop
		mShouldRunLoop = false;
	}
	else if (theEvent.getType() == DELETE_UNIT)
	{
		const DeleteUnit& removeUnit = static_cast<const DeleteUnit&>(theEvent);
		//Delete unit
		mpUnitManager->deleteUnit(removeUnit.getX(), removeUnit.getY(), 60);

	}
	else if (theEvent.getType() == CREATE_UNIT)
	{
		const CreateUnit& newUnit = static_cast<const CreateUnit&>(theEvent);
		//Spawn unit
		mpUnitManager->createNewUnit(mpNormalSmurf, newUnit.getX(), newUnit.getY());

	}

	//For later implementation:
	//mpPlayerUnit->mUnitAnimation->speedUp();
	//mpPlayerUnit->mUnitAnimation->slowDown();

}

void Game::initGame(int screenX, int screenY, string filename, EventSystem* eventSystem)
{
	//Init system (including screen size + FPS)
	//Have system init GraphicsLib
	
	mDisplayX = screenX;
	mDisplayY = screenY;

	mpGameSystem = new System(mDisplayX, mDisplayY);
	mpBufferManager = new GBufferManager();
	mpUnitManager = new UnitManager();
	
	mpGameSystem->initSystem();

	mpInputSystem = new InputSystem();
	mpInputSystem->init(mpGameSystem, eventSystem);

	mpBufferManager->createNewBuffer("BG", ASSET_PATH, filename);
	mpBufferManager->createNewBuffer("Smurfs", ASSET_PATH, SMURFS);
	mpBufferManager->createNewBuffer("Deans", ASSET_PATH, DEANS);

	//Backgound conversion for drawing
	mpGameBackground = new Sprite(mpBufferManager->getBuffer("BG"),0, 0, mDisplayX, mDisplayY);

	//new smurf animation
	mpNormalSmurf = new Animation(mpBufferManager->getBuffer("Smurfs"), 100.0, true);
	mpNormalSmurf->setAnimID(1);
	//new dean animation
	mpDeanSmurf = new Animation(mpBufferManager->getBuffer("Deans"), 100.0, true);
	mpDeanSmurf->setAnimID(2);
}

void Game::cleanupGame()
{
	
	delete mpInputSystem;
	delete mpGameBackground;
	delete mpNormalSmurf;
	delete mpDeanSmurf;

	//call system cleanup
	delete mpUnitManager;
	

	//mpBufferManager->clearAllBuffers();
	delete mpBufferManager;
	
	
	

	delete mpGameSystem;

	
}

void Game::runGameLoop()
{
	mShouldRunLoop = true;

	PerformanceTracker loopTracker;
	Timer mGameTimer;

	while (mShouldRunLoop)
	{

		loopTracker.clearTracker("GameLoop");
		loopTracker.startTracking("GameLoop");
	
		mGameTimer.start();
		
		// Process user input
		mpInputSystem->update();

		//Update
		mpUnitManager->update(16.7);

		//Draw 
		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);
		mpUnitManager->draw(mpGameSystem);
		
		
		//Display picture
		mpGameSystem->getDisplay()->flipDispaly();

		//get current time again
		double postTime = mGameTimer.getElapsedTime();

		//sleep time = target time - elapsed time
		double sleepTime = mTargetTime;

		//sleep for (sleep time) - al_rest
		mGameTimer.sleepUntilElapsed(sleepTime);

		loopTracker.stopTracking("GameLoop");
		cout << loopTracker.getElapsedTime("GameLoop") << endl; 

	}
}