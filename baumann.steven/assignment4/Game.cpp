#include "Game.h"
#include <iostream>
#include <iomanip>
using namespace std;

Game* Game::mpGameInstance = nullptr;

Game::Game(){}

Game::Game(int width, int height, float fps) 
{
	mFramesPerSecond = (1.0 / fps) * 1000;
	mpSys = new System(width, height, mFramesPerSecond);
	mHeight = height;
	mWidth = width;
}

void Game::init() 
{
	if (!mIsInitted) 
	{
		mpPerformanceTracker = new PerformanceTracker;
		mpUnitManager = new UnitManager();
		mpGBManager = new GraphicsBufferManager();
		mpCurrentMousePos = new int[2];
		mpCurrentMousePos[0] = mWidth / 2;
		mpCurrentMousePos[1] = mHeight / 2;
		mpSys->init();
		mIsCleanedUp = false;
		mIsInitted = true;
	}
	
}

void Game::createBuffer(string bufferName, string filename, int width, int height)
{ 
	GraphicsBuffer* newGb = new GraphicsBuffer(filename);
	mpGBManager->addBuffer(newGb);

	Sprite* newGbSprite = new Sprite(newGb, 0, 0, width, height);
	mSprites.insert({ bufferName, newGbSprite });
}

void Game::createAnimation(string animationName, string filename, int dimensions) 
{
	GraphicsBuffer* newGb = new GraphicsBuffer(filename);
	vector<GraphicsBuffer*> targetGb;
	mpGBManager->addBuffer(newGb);
	Animation* newAnim = mpSys->createAnimation(newGb, targetGb, dimensions);
	for (auto i : targetGb)
	{
		mpGBManager->addBuffer(i);
	}
	mAnimations.insert({ animationName, newAnim });

	//delete newGb;
}

void Game::createUnit(string unitName) 
{
	Unit* newUnit = new Unit();
	mpUnitManager->addUnit(unitName, newUnit);
}

void Game::addAnimationToUnit(string unitName, string animationName) 
{
	Unit* unitToChange = mpUnitManager->getUnit(unitName);
	unitToChange->addAnimation(mAnimations.find(animationName)->second);
}

void Game::drawBackground(string bufferName, int x, int y, float scale)
{
	Sprite* newSprite = mSprites.find(bufferName)->second;
	mAlwaysDraw.push_back(newSprite);
}

void Game::swapOnEnter(string unitName)
{
	mSwapOnEnter.push_back(mpUnitManager->getUnit(unitName));
}

void Game::drawUnitAtMouse(string unitName)
{
	mAlwaysAnimate.push_back(mpUnitManager->getUnit(unitName));
}

void Game::createOnMouseDown(string unitName)
{
	mpUnitManager->addAlwaysCreate(unitName);
}

void Game::InstantiateAtMouse(Unit* unitName, int offset)
{
	Unit* newInstance = new Unit(unitName, mpCurrentMousePos);
	newInstance->draw(mpSys, 1, offset);
	mpUnitManager->addToStorage(newInstance);
}

void Game::doLoop() 
{
	const int MOUSE_OFFSET = 30;
	const float UNIT_SCALE = 1.0;
	mTimer.start();
	double lastTime = 0;
	while (true) 
	{
		mpPerformanceTracker->clearTracker(mLOOP_TRACKER);
		mpPerformanceTracker->startTracking(mLOOP_TRACKER);

		mTimer.start();

		//Draw background image(s)
		for (auto i : mAlwaysDraw) 
		{
			mpSys->draw(0, 0, i, UNIT_SCALE);
		}

		if (mMouseDown) 
		{

			mpCurrentMousePos = mpSys->getMouseState();
			
		}

		if (mRightMouseDown) {
			mpCurrentMousePos = mpSys->getMouseState();
			mpUnitManager->removeAtCoords(mpCurrentMousePos);
		}

		if (mSwapNow) 
		{
			for (auto i : mSwapOnEnter) 
			{
				i->incrementAnimation();
			}
			mSwapNow = false;

			mpUnitManager->incrementLastSpriteAnimation();
		}

		switch (mSpeedUp) 
		{
		case System::eventType::SpeedUp:
			for (auto i : mSwapOnEnter)
			{
				i->speedUp();
			}
			mSpeedUp = 0;
			break;
		case System::eventType::SlowDown:
			for (auto i : mSwapOnEnter)
			{
				i->slowDown();
			}
			mSpeedUp = 0;
			break;
		}

		for (auto i : mAlwaysAnimate) 
		{
			i->updateLocation(mpCurrentMousePos[0], mpCurrentMousePos[1]);
			i->draw(mpSys, UNIT_SCALE, MOUSE_OFFSET);
		}

		mpUnitManager->instantiateAtMouse(mMouseDown, mpCurrentMousePos, mpSys, MOUSE_OFFSET);

		lastTime += mTimer.getElapsedTime();
		
		mpUnitManager->update(lastTime);
		mpUnitManager->draw(mpSys, UNIT_SCALE, MOUSE_OFFSET);

		mpSys->flip();

		//Waits until we have input to do anything. If no input is found, waits until the end of the frame.
		int found = 0;
		while (mTimer.getElapsedTime() < mFramesPerSecond) 
		{
			found = mpSys->waitForEvent();
			if (found == System::eventType::MouseChanged)
			{
				mMouseDown = !mMouseDown;
			}
			else if (found == System::eventType::EnterKey)
			{
				mSwapNow = true;
			}
			else if (found == System::eventType::FKey)
			{
				mSpeedUp = System::eventType::SpeedUp;
			}
			else if (found == System::eventType::SKey)
			{
				mSpeedUp = System::eventType::SlowDown;
			}
			else if (found == System::eventType::EscapeKey)
			{
				mExitNow = true;
			}
			else if (found == System::eventType::SpaceKey)
			{
				mpUnitManager->swapFrozen();
			}
			else if (found == System::eventType::RemoveSprite)
			{
				mRightMouseDown = !mRightMouseDown;
			}
		}

		mTimer.sleepUntilElapsed(mFramesPerSecond);

		mpPerformanceTracker->stopTracking(mLOOP_TRACKER);
		std::cout << endl << "loop time: " << setprecision(4) << 1/(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER)/1000) << " FPS";

		if (mExitNow) 
		{
			break;
		}
	}
}

void Game::cleanup() 
{

	if (!mIsCleanedUp) 
	{

		delete mpSys;

		delete mpCurrentMousePos;

		delete mpPerformanceTracker;

		delete mpUnitManager;

		for (auto const& i : mSprites)
		{
			delete i.second;
		}
		
		delete mpGBManager;

		mIsCleanedUp = true;
		mIsInitted = false;

		delete(this);

	}
	
}

Game::~Game() 
{
	if (!mIsCleanedUp) {
		cleanup();
	}
	
}