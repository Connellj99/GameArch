#include "Game.h"
#include <PerformanceTracker.h>

Game* Game::mpsGameInstance = nullptr;

Input Game::checkInput()
{
	Input temp;
	if (mSystem->getKeyDown(ESCAPE))
	{
		temp.escKey = true;
	}
	if (mSystem->getKeyDown(ENTER))
	{
		temp.enterKey = true;
	} 
	if (mSystem->getButtonDown(Left_Click).down)
	{
		temp.leftClick = true;
		temp.clickPos = mSystem->getButtonDown(Left_Click).position;
	}
	if (mSystem->getButtonDown(Right_Click).down)
	{
		temp.rightClick = true;
		temp.clickPos = mSystem->getButtonDown(Right_Click).position;
	}
	if (mSystem->getKeyDown(SPACE))
	{
		temp.spaceKey = true;
	}
	return temp;
}

void Game::render()
{
	mSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, WOODS_SCALE);
	mUnitManager.updateUnit();
	mUnitManager.draw();
	mSystem->getGraphicsSystem()->flip();
}

void Game::update(Input currentInput)
{
	if (currentInput.escKey)
	{
		mLoopGame = false;
	}
	if (currentInput.enterKey)
	{
		mUnitManager.getUnit()->swapAnimations();
	}
	if (currentInput.spaceKey)
	{
		mUnitManager.pausePlayAllUnits();
	}
	if (currentInput.rightClick)
	{
		Vector2D loc = currentInput.clickPos;
		mUnitManager.deleteByPosition(loc);
	}
	if (currentInput.leftClick)
	{
		Vector2D loc = currentInput.clickPos;
		loc-= Vector2D(30, 30);
		vector<Animation> temp;
		temp.push_back(Animation(*mBufferManager.getBuffer(SMURF_KEY), SMURF_SPRITE_SIZE));
		temp.push_back(Animation(*mBufferManager.getBuffer(DEAN_KEY), SMURF_SPRITE_SIZE));
		mUnitManager.createUnit(temp, loc);
	}
	mUnitManager.updateUnit();
}


Game::Game()
{
	mpWoodsSprite = nullptr;
}

Game::~Game()
{
	cleanup();
}

void Game::initInstance()
{
	//as long as no other deal is there make one
	if (mpsGameInstance == nullptr)
	{
		mpsGameInstance = new Game;
	}
	else
	{
		assert(mpsGameInstance != nullptr);
	}
	
}

void Game::cleanupInstance()
{
	delete mpsGameInstance;
	mpsGameInstance = nullptr;
}

void Game::doLoop()
{
	PerformanceTracker tracker = PerformanceTracker();
	while (mLoopGame)
	{
		tracker.clearTracker(TRACKER);
		tracker.startTracking(TRACKER);
		mTimer.start();
		//--
		Input currentInput = checkInput();
		update(currentInput);
		render();
		mTimer.sleepUntilElapsed(mframeTime);
		//--
		tracker.stopTracking(TRACKER);
		cout << tracker.getElapsedTime(TRACKER) << endl;
	}
}

Game * Game::getInstance()
{
	assert(mpsGameInstance);
	return mpsGameInstance;
}

void Game::init(Vector2D screenSize, float targetFrameRate)
{
	mSystem = new System();
	mSystem->init();
	mBufferManager = GraphicsBufferManager();
	mUnitManager = UnitManager();

	//Set screen and frame variables
	mScreenSize = screenSize;
	mframeTime = 1000 / targetFrameRate;

	//create buffers and add to manager
	mBufferManager.addBuffer(WOODS_KEY  ,new GraphicsBuffer(SHARED_PATH + BACKGROUND_FILENAME));
	mBufferManager.addBuffer(SMURF_KEY, new GraphicsBuffer(SHARED_PATH + SMURF_FILENAME));
	mBufferManager.addBuffer(DEAN_KEY, new GraphicsBuffer(SHARED_PATH + DEAN_FILENAME));

	mpWoodsSprite = new Sprite(mBufferManager.getBuffer(WOODS_KEY), Vector2D(0, 0), Vector2D(mBufferManager.getBuffer(WOODS_KEY)->getWidth(), mBufferManager.getBuffer(WOODS_KEY)->getHeight()));

}

void Game::cleanup()
{
	delete mpWoodsSprite;
	mpWoodsSprite = nullptr;
	mSystem->cleanup();
	delete mSystem;
	mSystem = nullptr;
}

System* Game::getSystem()
{
	return mSystem;
}
