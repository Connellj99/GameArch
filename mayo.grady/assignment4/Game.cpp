/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Game.h"

Game * Game::mpGameInstance = nullptr;

Game::Game()
{
	mpSystem = new System();
}

Game::~Game()
{
	cleanup();
}

void Game::init()
{
	mIsInitted = true;
	//Create performance tracker
	mpTracker = new PerformanceTracker();

	//Init system
	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);

	//set up managers
	mpGBManager = new GraphicsBufferManager;
	mpUnitManager = new UnitManager;

	//Create buffers
	mpGBManager->add(WOODS_KEY, ASSET_PATH + WOODS_FILENAME);
	mpGBManager->add(SMURF_KEY, ASSET_PATH + SMURFS_FILENAME);
	mpGBManager->add(DEAN_KEY, ASSET_PATH + DEAN_FILENAME);

	//Create Animations
	mpSmurfsAnimation = new Animation();
	mpDeanAnimation = new Animation();

	//Add sprites to animations
	mpSmurfsAnimation->addSprite(mpGBManager->getBuffer(SMURF_KEY), SMURF_COLS_ROWS);
	mpDeanAnimation->addSprite(mpGBManager->getBuffer(DEAN_KEY), SMURF_COLS_ROWS);
}

void Game::cleanup()
{
	if (mIsInitted)
	{
		mIsInitted = false;
		
		delete mpDeanAnimation;
		delete mpSmurfsAnimation;
		delete mpTracker;
		mpUnitManager->cleanup();
		delete mpUnitManager;
		mpGBManager->cleanup();
		delete mpGBManager;

		delete mpSystem;
	}
}

void Game::doLoop()
{
	while (mKeepGoing)
	{
		//performance tracker -> start
		mpTracker->clearTracker(TRACKER);
		mpTracker->startTracking(TRACKER);

		mTheTimer.start();

		//loop processing
		//draw statements
		render();

		//check user input
		checkInput();

		//update to next animation frame
		mpUnitManager->update(FPS_CONVERSION);
		
		mTheTimer.sleepUntilElapsed(FPS_CONVERSION);

		//performance tracker -> stop
		mpTracker->stopTracking(TRACKER);
		cout << mpTracker->getElapsedTime(TRACKER) << endl;
	}
}

void Game::checkInput()
{
	mpSystem->getMouseState();
	if (mpSystem->getMouseButton() == 1)
	{
		int xPos = mpSystem->getMouseX() - SMURF_SIDE / 2;
		int yPos = mpSystem->getMouseY() - SMURF_SIDE / 2;
		mpUnitManager->add(Vector2D(xPos, yPos));
		mpUnitManager->getUnit(mpUnitManager->getCollectionSize() - 1)->setAnimation(mpSmurfsAnimation);
	}
	if (mpSystem->getMouseButton() == 2)
	{
		int xPos = mpSystem->getMouseX() - SMURF_SIDE / 2;
		int yPos = mpSystem->getMouseY() - SMURF_SIDE / 2;
		mpUnitManager->remove(Vector2D(xPos, yPos));
	}
	if (mpSystem->getKeyState() == "SPACE")
	{
		mpUnitManager->toggleAnim();
	}
	if (mpSystem->getKeyState() == "ENTER")
	{
		if (mCurrentAnimation == 0)
		{
			//cout << "change to dean animation" << endl;
			mCurrentAnimation = 1;
			mpUnitManager->getUnit(mpUnitManager->getCollectionSize() - 1)->setAnimation(mpDeanAnimation);
		}
		else
		{
			//cout << "change to smurf animation" << endl;
			mCurrentAnimation = 0;
			mpUnitManager->getUnit(mpUnitManager->getCollectionSize() - 1)->setAnimation(mpSmurfsAnimation);
		}
	}
	if (mpSystem->getKeyState() == "ESC")
	{
		mKeepGoing = false;
	}
}

void Game::render()
{
	//draw woods
	mpSystem->getGraphicsSystem()->draw(mpGBManager->getBuffer(WOODS_KEY), ZERO, ZERO, HALF_SCALE);

	//draw unit then update to next animation frame
	mpUnitManager->draw();

	//flip diaplay
	mpSystem->getGraphicsSystem()->flip();
}