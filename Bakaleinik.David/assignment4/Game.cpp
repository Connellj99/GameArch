#include "Game.h"
#include "Unit.h"
#include "System.h"
#include "Timer.h"
#include "GraphicsBuffer.h"
#include "PerformanceTracker.h"
#include "Animation.h"
#include "GBufferManager.h"
#include "UnitManager.h"

Game * Game::mpGameInstance = nullptr;

const int LEFT_MOUSE_BUTTON = 1;
const int RIGHT_MOUSE_BUTTON = 2;
const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string DEANS = "dean_sprites.png";
const string SMURFS = "smurf_sprites.png";

using namespace std;

Game* gpGame = nullptr;

Game::Game()
{

}

Game::Game(double fps)
{
	mTargetTime = fps;
}

Game::~Game()
{

}

void Game::initGame(int screenX, int screenY, string filename)
{
	//Init system (including screen size + FPS)
	//Have system init GraphicsLib
	
	mDisplayX = screenX;
	mDisplayY = screenY;

	mpGameSystem = new System(mDisplayX, mDisplayY);
	mpBufferManager = new GBufferManager();
	mpUnitManager = new UnitManager();
	
	mpGameSystem->initSystem();

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
	
	delete mpGameBackground;
	delete mpNormalSmurf;
	delete mpDeanSmurf;

	//call system cleanup
	delete mpUnitManager;
	

	//mpBufferManager->clearAllBuffers();
	delete mpBufferManager;
	
	
	mpGameSystem->cleanupSystem();
	delete mpGameSystem;
}

void Game::runGameLoop()
{
	bool shouldStop = true;

	PerformanceTracker loopTracker;
	Timer mGameTimer;

	while (shouldStop)
	{

		loopTracker.clearTracker("GameLoop");
		loopTracker.startTracking("GameLoop");
	
		mGameTimer.start();
		
		//Process Mouse Input:
		bool rightMouseClicked = false;
		bool leftMouseClicked = false;

		rightMouseClicked = mpGameSystem->getMouseState(LEFT_MOUSE_BUTTON);
		leftMouseClicked = mpGameSystem->getMouseState(RIGHT_MOUSE_BUTTON);
		

		if (rightMouseClicked)
		{
			mpUnitManager->createNewUnit(mpNormalSmurf, mpGameSystem->getMouseX(), mpGameSystem->getMouseY());
			
		}
		
		if (leftMouseClicked)
		{
			//mpUnitManager->deleteUnit(,);
			//Collision detection:
			//For every Unit in the map - get the unit's (x, y)+sprite size
			//spriteposX @ origin & spriteposY @ orgin (greater) || spriteposX + size & spriteposy + size (less)
			//Delete that unit

				//Unit needs 2 new functions + a bool
				//1 - check collision; 2 - toggles the bool, which controlls whether animation's update is called.
			mpUnitManager->deleteUnit(mpGameSystem->getMouseX(), mpGameSystem->getMouseY(), 60);
		}

		//Process Keyboard Input
		string key = mpGameSystem->getKeyState();
		//string key = "";

		if (key == "F")
		{
			//mpPlayerUnit->mUnitAnimation->speedUp();
		}
		else if (key == "S")
		{
			//mpPlayerUnit->mUnitAnimation->slowDown();
		}
		else if (key == "Esc")
		{
			shouldStop = false;
		}
		else if (key == "Ent")
		{
			mpUnitManager->switchHead(mpDeanSmurf, mpNormalSmurf);
		}
		else if (key == "Space")
		{
			//Sets a bool flag to false
			mpUnitManager->disableAnimation();
		}

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