#include "Game.h"
#include "Unit.h"
#include "System.h"
#include "Timer.h"
#include "GraphicsBuffer.h"
#include "PerformanceTracker.h"
#include "Animation.h"

const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string DEANS = "dean_sprites.png";
const string SMURFS = "smurf_sprites.png";
const int LEFT_MOUSE_BUTTON = 1;
const int RIGHT_MOUSE_BUTTON = 2;

using namespace std;

Game* gpGame = NULL;

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

	mpGameSystem->initSystem();

	//Create the background image
	mpBackgroundBuffer = new GBuffer(ASSET_PATH, filename);//make new gbuffer - give it the filename
	mpGameBackground = new Sprite(mpBackgroundBuffer,0, 0, mDisplayX, mDisplayY);

	//call draw from the game loop

	mpSmurfSheet = new GBuffer(ASSET_PATH, SMURFS);

	mpDeanSheet = new GBuffer(ASSET_PATH, DEANS);

	//new smurf animation
	mpNormalSmurf = new Animation(mpSmurfSheet, 100.0, true);
	
	//new dean animation
	mpDeanSmurf = new Animation(mpDeanSheet, 100.0, true);

	mpPlayerUnit = new Unit(mpNormalSmurf, mDisplayX/2, mDisplayY/2); //Creates unit at the center of the screen
}

void Game::cleanupGame()
{
	
	delete mpGameBackground;
	delete mpBackgroundBuffer;

	delete mpNormalSmurf;
	delete mpDeanSmurf;

	delete mpDeanSheet;
	delete mpSmurfSheet;

	delete mpPlayerUnit;
	//call system cleanup
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
		bool mouseClicked = false;

		mouseClicked = mpGameSystem->getMouseState(LEFT_MOUSE_BUTTON);

		

		if (mouseClicked)
		{
			mpPlayerUnit->setXLoc(mpGameSystem->getMouseX());
			mpPlayerUnit->setYLoc(mpGameSystem->getMouseY());
		}
		

		//Process Keyboard Input
		string key = mpGameSystem->getKeyState();
		//string key = "";

		if (key == "F")
		{
			mpPlayerUnit->mUnitAnimation->speedUp();
		}
		else if (key == "S")
		{
			mpPlayerUnit->mUnitAnimation->slowDown();
		}
		else if (key == "Esc")
		{
			shouldStop = false;
		}
		else if (key == "Ent")
		{
			if (mpPlayerUnit->mUnitAnimation == mpNormalSmurf)
			{
				mpPlayerUnit->setUnitAnimation(mpDeanSmurf);
			}
			else
			{
				mpPlayerUnit->setUnitAnimation(mpNormalSmurf);
			}
			
		}

		mpPlayerUnit->update(16.7);

		//Draw the updated Unit
		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);
		mpPlayerUnit->drawUnit(mpGameSystem);
		
		mpGameSystem->getDisplay()->flipDispaly();

		//get current time again
		double postTime = mGameTimer.getElapsedTime();

		//sleep time = target time - elapsed time
		double sleepTime = mTargetTime - postTime;

		//sleep for (sleep time) - al_rest
		mGameTimer.sleepUntilElapsed(sleepTime);

		loopTracker.stopTracking("GameLoop");
		cout << loopTracker.getElapsedTime("GameLoop");

	}

	

}