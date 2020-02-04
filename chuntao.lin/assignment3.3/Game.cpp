#include "Game.h"
#include "Unit.h"

Game* gGameObj = NULL;

Game::Game()
{
	initGameSystems();
}

Game::~Game()
{
	cleanUpGame();

	//delete and therefore call the game system destructor
	delete mpGameSystem;
	mpGameSystem = NULL;
}

void Game::initGameSystems()
{
	mpGameSystem = new System;
	mpGameSystem->mpGraphicSys->initGraphicSys();
}

void Game::drawStartingData(std::string filePath, std::string filePath2,std:: string filePath3)
{
	//For drawing the first image
	Sprite* backgroundSprite = new Sprite;

	mpBackgroundBuff = new GraphicsBuffer(filePath);

	backgroundSprite->setSprite(*mpBackgroundBuff, filePath);//set the appropriate buffer to the one with inputed file.

	//for drawing second image
	Sprite* unitSprite = new Sprite;

	mpSpriteBuff = new GraphicsBuffer(filePath2);

	unitSprite->setSprite(*mpSpriteBuff, filePath2);//call the sprites set sprite function that will take in the buffer and filepath
	
	unitSprite->setSpriteSourceLocation(*mpSpriteBuff);

	//for drawing third image 
	Sprite* unit2Sprite = new Sprite;

	mpSprite2Buff = new GraphicsBuffer(filePath3);

	unit2Sprite->setSprite(*mpSprite2Buff, filePath3);//call the sprites set sprite function that will take in the buffer and filepath

	unit2Sprite->setSpriteSourceLocation(*mpSprite2Buff);

	mpSpriteOneAnimation = new Animations(60.0, true);	//create the sprite one animation

	initializeSmurfs(mpSpriteBuff,0);//initlalize the first sprite with appropriate buffer and animation destination

	mpSpriteTwoAnimation = new Animations(60.0, true);//create the sprite two animation

	initializeSmurfs(mpSprite2Buff,1);//initlalize the second sprite with appropriate buffer and animation destination
	
	mpAnimationVector.push_back(mpSpriteOneAnimation);
	mpAnimationVector.push_back(mpSpriteTwoAnimation);

	mpSpriteUnitVector.push_back(new Unit(400, 300, mpAnimationVector));
	
	//deallocate the memory previosly allocated.
	delete backgroundSprite;
	delete unitSprite;
	delete unit2Sprite;

	backgroundSprite = NULL;
	unitSprite = NULL;
	unit2Sprite = NULL;
}

void Game::gameLoop()
{
	Timer timer;
	do
	{
		timer.start();//start the tinme
		
		getUserInput();//get the user input

		adjustGameState();//adjust and change game state

		drawCurrentData();//draw the newer game state

		timer.sleepUntilElapsed(mSleepAmount);//sleep until the sleep amount

		std::cout << "Time per each frame: " << timer.getElapsedTime() << " ms" << std::endl; // Report elapsed time


	} while (mpGameSystem->mGameDone == false);
	system("cls");
}

void Game::cleanUpGame()
{
		
	//delete the member pointer buffers that are in the Game class
	delete mpBackgroundBuff;
	mpBackgroundBuff = NULL;
	delete mpSpriteBuff;
	mpSpriteBuff = NULL;
	delete mpSprite2Buff;
	mpSprite2Buff = NULL;

	// call the destructor of animation for each sprite
	delete mpSpriteOneAnimation;
	mpSpriteOneAnimation = NULL;
	delete mpSpriteTwoAnimation;
	mpSpriteTwoAnimation = NULL;


	for (int i = 0; i < mpSpriteUnitVector.size(); i++)
	{
		delete mpSpriteUnitVector[i];//delete each of the vector contents

	}
	mpSpriteUnitVector.clear();//clear it in case
}

void Game::getUserInput()
{
	mpGameSystem->getKeyState(mUnitOnScreen);//call the get key state from the system
	mpGameSystem->getMouseState(mUnitOnScreen);//call the get mouse state from the system.
}

void Game::drawCurrentData()
{
	mpGameSystem->mpGraphicSys->drawBackBuffer(0, 0, *mpBackgroundBuff, 0.5);//draw to backbuffer
	bool swap = mpGameSystem->getAnimationSwitchStatus();//get the current status of if the animation can switch

	for (Unit* unit : mpSpriteUnitVector)//goe through teach unit
	{
		unit->drawCurrentAnimation(mpGameSystem,swap);//pass in the system and the swap bool
		mUnitOnScreen = unit->getUnitScreenStatus();
	}

	mpGameSystem->mpGraphicSys->flipDisplay();//flip display to show the images.

	mpGameSystem->mSpeedGameUp = false;//reset the systems can speed up bools.
	mpGameSystem->mSpeedGameDown = false;
}

void Game::adjustGameState()
{
	for (Unit* unit : mpSpriteUnitVector)//go through each unit and update
	{
		unit->updateUnitState(mSleepAmount/CONVERT_MS_TO_SEC, mpGameSystem->getSpeedUpStatus(), mpGameSystem->getSpeedDownStatus());
		
	}
}

void Game::initializeSmurfs(GraphicsBuffer* spriteObj,int spriteNum)
{
	switch (spriteNum)
	{
	case 0://take the passed in graphic buffer and based on which spriteNum it is, set that animation to the call of the chopspritesheet function
		mpSpriteOneAnimation->chopSpriteSheet(*spriteObj);
		break;

	case 1://same as above
		mpSpriteTwoAnimation->chopSpriteSheet(*spriteObj);
		break;
	}
		
}