#include "Game.h"
#include <iostream>
#include <iomanip>
using namespace std;

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
	mpPerformanceTracker = new PerformanceTracker;
	mpCurrentMousePos = new int[2];
	mpCurrentMousePos[0] = mWidth/2;
	mpCurrentMousePos[1] = mHeight/2;
	mpSys->init();
}

void Game::createBuffer(string bufferName, string filename, int width, int height)
{ 
	GraphicsBuffer* newGb = new GraphicsBuffer(filename);
	mBuffers.insert({ bufferName, newGb });

	Sprite* newGbSprite = new Sprite(newGb, 0, 0, width, height);
	mSprites.insert({ bufferName, newGbSprite });
}

void Game::createAnimation(string animationName, string filename, int dimensions) 
{
	GraphicsBuffer* newGb = new GraphicsBuffer(filename);
	Animation* newAnim = mpSys->createAnimation(newGb, dimensions);

	mAnimations.insert({ animationName, newAnim });

	delete newGb;
}

void Game::createUnit(string unitName) 
{
	Unit* newUnit = new Unit();
	mUnits.insert({ unitName, newUnit });
}

void Game::addAnimationToUnit(string unitName, string animationName) {
	Unit* unitToChange = mUnits.find(unitName)->second;
	unitToChange->addAnimation(mAnimations.find(animationName)->second);
}

void Game::drawBackground(string bufferName, int x, int y, float scale)
{
	Sprite* newSprite = mSprites.find(bufferName)->second;
	mAlwaysDraw.push_back(newSprite);
}

void Game::drawAnimation(Unit* unitName, float scale, float offset)
{
	Sprite* newSprite = unitName->getAnimation()->getCurrentSprite();
	mpSys->draw(mpCurrentMousePos[0] - offset, mpCurrentMousePos[1] - offset, newSprite, scale);
	unitName->update();
}

void Game::swapOnEnter(string unitName)
{
	mSwapOnEnter.push_back(mUnits.find(unitName)->second);
}

void Game::drawUnitAtMouse(string unitName)
{
	mAlwaysAnimate.push_back(mUnits.find(unitName)->second);
}

void Game::doLoop() 
{
	const int MOUSE_OFFSET = 30;
	while (true) 
	{
		mpPerformanceTracker->clearTracker(mLOOP_TRACKER);
		mpPerformanceTracker->startTracking(mLOOP_TRACKER);

		mTimer.start();

		//Draw background image(s)
		for (auto i : mAlwaysDraw) 
		{
			mpSys->draw(0, 0, i, 1);
		}

		if (mMouseDown) {

			mpCurrentMousePos = mpSys->getMouseState();
			
		}

		if (mSwapNow) {
			for (auto i : mSwapOnEnter) 
			{
				i->incrementAnimation();
			}
			mSwapNow = false;
		}

		switch (mSpeedUp) {
		case 2:
			for (auto i : mSwapOnEnter)
			{
				i->getAnimation()->speedUp();
			}
			mSpeedUp = 0;
			break;
		case 1:
			for (auto i : mSwapOnEnter)
			{
				i->getAnimation()->slowDown();
			}
			mSpeedUp = 0;
			break;
		}

		for (auto i : mAlwaysAnimate) 
		{
			drawAnimation(i, 1, MOUSE_OFFSET);
		}

		mpSys->flip();

		//Waits until we have input to do anything. If no input is found, waits until the end of the frame.
		int found = 0;
		while (mTimer.getElapsedTime() < mFramesPerSecond) {
			found = mpSys->waitForEvent();
			if (found == 1)
			{
				mMouseDown = !mMouseDown;
				break;
			}
			else if (found == 2) 
			{
				mSwapNow = true;
			}
			else if (found == 3) 
			{
				mSpeedUp = 1;
			}
			else if (found == 4) 
			{
				mSpeedUp = 2;
			}
			else if (found == 5)
			{
				mExitNow = true;
			}
		}

		mTimer.sleepUntilElapsed(mFramesPerSecond);

		mpPerformanceTracker->stopTracking(mLOOP_TRACKER);
		cout << endl << "loop time: " << setprecision(4) << 1/(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER)/1000) << " FPS";

		if (mExitNow) {
			break;
		}
	}
}

void Game::cleanup() {

	delete mpSys;

	delete mpCurrentMousePos;

	delete mpPerformanceTracker;

	for (auto const& i : mUnits)
	{
		delete i.second;
	}

	for (auto const& i : mSprites)
	{
		delete i.second;
	}
	
}

Game::~Game() 
{
}