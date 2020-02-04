/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Game.h"

Game * gpGame = NULL;

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
	//Init system
	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);

	//Create buffers
	mpWoodsBuffer = mpSystem->createBuffer(ASSET_PATH + WOODS_FILENAME);
	mpSmurfsBuffer = mpSystem->createBuffer(ASSET_PATH + SMURFS_FILENAME);
	mpDeanBuffer = mpSystem->createBuffer(ASSET_PATH + DEAN_FILENAME);

	//Create Animations
	mpSmurfsAnimation = new Animation();
	mpDeanAnimation = new Animation();

	//Add sprites to animations
	mpSmurfsAnimation->addSprite(mpSmurfsBuffer, SMURF_COLS_ROWS);
	mpDeanAnimation->addSprite(mpDeanBuffer, SMURF_COLS_ROWS);

	//Create Unit and add first animation
	mpUnit = new Unit(CENTER_X, CENTER_Y);
	mpUnit->setAnimation(mpSmurfsAnimation);
}

void Game::cleanup()
{
	if (mIsInitted)
	{
		mIsInitted = false;
		delete mpUnit;
		delete mpDeanAnimation;
		delete mpSmurfsAnimation;
		delete mpDeanBuffer;
		delete mpSmurfsBuffer;
		delete mpWoodsBuffer;
		delete mpSystem;
	}
}

void Game::doLoop()
{
	while (keepGoing)
	{
		//performance tracker -> clear tracker
		//performance tracker -> start

		theTimer.start();

		//loop processing
		//draw woods
		mpSystem->getGraphicsSystem()->draw(mpWoodsBuffer, ZERO, ZERO, HALF_SCALE);

		//check user input
		checkInput();

		//draw unit then update to next animation frame
		mpUnit->draw(unitLocX, unitLocY);
		//cout << "start unit update" << endl;
		mpUnit->update();

		//flip diaplay
		mpSystem->getGraphicsSystem()->flip();

		theTimer.sleepUntilElapsed(FPS_CONVERSION);

		//performance tracker -> stop
		//cout << report
	}
}

void Game::checkInput()
{
	mpSystem->getMouseState();
	if (mpSystem->getMouseButton() == 1)
	{
		unitLocX = mpSystem->getMouseX();
		unitLocY = mpSystem->getMouseY();
	}
	if (mpSystem->getKeyState() == "F")
	{
		//cout << "speed up" << endl;
		mpUnit->getAnimation()->changeSpeed(-10.0);
	}
	if (mpSystem->getKeyState() == "S")
	{
		//cout << "slow down" << endl;
		mpUnit->getAnimation()->changeSpeed(10.0);
	}
	if (mpSystem->getKeyState() == "ENTER")
	{
		if (currentAnimation == 0)
		{
			//cout << "change to dean animation" << endl;
			currentAnimation = 1;
			mpUnit->setAnimation(mpDeanAnimation);
		}
		else
		{
			//cout << "change to smurf animation" << endl;
			currentAnimation = 0;
			mpUnit->setAnimation(mpSmurfsAnimation);
		}
	}
	if (mpSystem->getKeyState() == "ESC")
	{
		keepGoing = false;
	}
}