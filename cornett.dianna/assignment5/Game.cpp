/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#include "Game.h"
#include <cassert>

Game * Game::mpsInstance = NULL;

/*
Create a Game object
*/
Game::Game() 
{

}

/*
Destory the game
*/
Game::~Game() 
{
	cleanup();
}

/*
Initilize mpsInstance
*/
void Game::initInstance()
{
	if (mpsInstance == NULL)
	{
		mpsInstance = new Game();
	}
}

/*
Delete mpsInstance if it is innited
*/
void Game::cleanupInstance()
{
	if (mpsInstance != NULL)
	{
		delete mpsInstance;
		mpsInstance = NULL;
	}
}

/*
Get mpsInstance
*/
Game* Game::getInstance()
{
	assert(mpsInstance != NULL);
	return mpsInstance;
}


/*
Initilize everything needed by game
*/
void Game::init()
{
	mIsInit = true;
	//Set the game pointer to game

	//Make and init the graphics system
	mpSystem = new System;
	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);

	//Make the graphics buffer
	mpGraphicsBufferManager = new GraphicsBufferManager;
	
	//Make the unit manager
	mpUnitManager = new UnitManager();
	
	//Create the animations and sprites
	//Make graphics buffers
	mpGraphicsBufferManager->addBuffer("deanSprites", new GraphicsBuffer(ASSET_PATH + DEAN_SMURF_FILENAME));
	mpGraphicsBufferManager->addBuffer("smurfSprites", new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME));
	mpGraphicsBufferManager->addBuffer("woodsBackground", new GraphicsBuffer(ASSET_PATH + WOODS_FILENAME));


	//Get the size of each sprite. Assuming dean sprites are same size as smurf sprites
	spriteWidth = mpGraphicsBufferManager->getBuffer("smurfSprites")->getWidth() / SMURF_SHEET_COLS;
	spriteHeight = mpGraphicsBufferManager->getBuffer("smurfSprites")->getWidth() / SMURF_SHEET_HIEGHT;

	
	//Make the animations
	Animation * smurf = new Animation(TIME_PER_SPRITE, true);
	Animation * dean = new Animation(TIME_PER_SPRITE, true);
	smurf->readInSprites(mpGraphicsBufferManager->getBuffer("smurfSprites"), SMURF_SHEET_COLS, SMURF_SHEET_HIEGHT);
	dean->readInSprites(mpGraphicsBufferManager->getBuffer("deanSprites"), SMURF_SHEET_COLS, SMURF_SHEET_HIEGHT);


	//Put the animations in a vector
	mAnimations.push_back(smurf);
	mAnimations.push_back(dean);
	
	//Add a unit containing the animations to the the list of units
	mpUnitManager->add(new Unit(mAnimations, Position(DISP_WIDTH/2, DISP_HEIGHT/2), spriteWidth, spriteHeight));

	mPerformanceTracker = new PerformanceTracker();
}


/*
Clean up all memory used
*/
void Game::cleanup()
{
	if (mIsInit)
	{
		mIsInit = false;

		//Delete all the other stuff
		if (mpUnitManager != NULL) 
		{
			delete mpUnitManager;
		}
		if (mpSystem != NULL)
		{
			delete mpSystem;
			mpSystem = NULL;
		}

		if (mpGraphicsBufferManager != NULL)
		{
			delete mpGraphicsBufferManager;
			mpGraphicsBufferManager = NULL;
		}

		if (mPerformanceTracker != NULL) {
			delete mPerformanceTracker;
		}
	}
	
}


/*
Add a unit to the list of units in the game
*/
void Game::addUnit(Unit * unit)
{
	mpUnitManager->add(unit);
}


/*
The fixed timestep game loop that performs all actions
*/
void Game::doLoop()
{
	//Have a loop
	do {

		//Start Clock
		mTheTimer.start();
		
		
		//Start tracker
		mPerformanceTracker->startTracking("frame");

		//INPUT SECTION
		//Check if enter was pressed and if so change the animation
		if (mpSystem->getKeyState(KeyCode::ENTER)) 
		{
			mpUnitManager->getLastUnit()->setAnimation();
		}
		

		if (mpSystem->getKeyState(KeyCode::SPACE)) {
			mPrevousIsAnimating = !mPrevousIsAnimating;
			mpUnitManager->setIsAnimating(mPrevousIsAnimating);
		}
		
		//Check if the mouse was pressed and if so set the position of the unit to the mouse position
		if (mpSystem->getMouseState(MouseCode::LEFT))
		{
			Position mousePos = mpSystem->getMousePosition();

			//Make a list of animations, read in the sprites
			std::vector<Animation*> newAnimations;
			Animation * newSmurf = new Animation(TIME_PER_SPRITE, true);
			Animation * newDean = new Animation(TIME_PER_SPRITE, true);
			newSmurf->readInSprites(mpGraphicsBufferManager->getBuffer("smurfSprites"), SMURF_SHEET_COLS, SMURF_SHEET_HIEGHT);
			newDean->readInSprites(mpGraphicsBufferManager->getBuffer("deanSprites"), SMURF_SHEET_COLS, SMURF_SHEET_HIEGHT);

			//Add animations to the list
			newAnimations.push_back(newSmurf);
			newAnimations.push_back(newDean);

			//Create a new unit and add it to the unit manager
			mpUnitManager->add(new Unit(newAnimations, mousePos, spriteWidth, spriteHeight));

		}

		if (mpSystem->getMouseState(MouseCode::RIGHT))
		{
			Position mousePos = mpSystem->getMousePosition();
			//Delete sprite they are clicked on
			mpUnitManager->deleteAtPosition(mousePos);
		}


		//UPDATE SECTION
		mpUnitManager->update(mTimestep / 1000.0);
		
		//DRAW SECTION 

		//Clear at the start of each frame 
		mpSystem->getGraphicsSystem()->clearToColor(Color(255, 255, 255));

		//Draw the backround
		mpSystem->getGraphicsSystem()->drawGraphicsBuffer(mpGraphicsBufferManager->getBuffer("woodsBackground"), 0, 0, .5);

		
		mpUnitManager->draw(mpSystem);


		//Refresh the screen
		mpSystem->getGraphicsSystem()->flip();

		
		//Wait for remander of the frame
		mTheTimer.sleepUntilElapsed(mTimestep);

		//Report time to do work
		mPerformanceTracker->stopTracking("frame");
		std::cout << "!!!!!!!!!!!!!!!!!Elapsed Time: " << mPerformanceTracker->getElapsedTime("frame") << "!!!!!!!!!!!!!!!!!!!!!\n";
		mPerformanceTracker->clearTracker("frame");
		
	} 
	while (!mpSystem->getKeyState(KeyCode::ESC)); //Exit if user clickes escape
}

/*
Getters for the systems and managers
*/
System * Game::getSystem() 
{
	return mpSystem;
}

GraphicsBufferManager * Game::getGraphicsBufferManager()
{
	return mpGraphicsBufferManager;
}

UnitManager * Game::getUnitManager() 
{
	return mpUnitManager;
}