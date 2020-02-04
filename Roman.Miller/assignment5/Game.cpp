#include "Event.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include "EventSystem.h"
#include "GameEvent.h"

Game* Game::mpsGameInstance = nullptr;

void Game::render()
{
	mSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, WOODS_SCALE);
	mUnitManager.updateUnit();
	mUnitManager.draw();
	mSystem->getGraphicsSystem()->flip();
}

void Game::update()
{
	mpInputSystem->update();
	mUnitManager.updateUnit();
}


Game::Game()
	:EventListener(EventSystem::getInstance())
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
		mpsGameInstance = new Game();

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
		update();
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
	mpInputSystem = new InputSystem();
	mpInputTranslator = new InputTranslator(EventSystem::getInstance());
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

	EventSystem::getInstance()->addListener((EventType)EXIT_GAME, this);
	EventSystem::getInstance()->addListener((EventType)CREATE, this);
	EventSystem::getInstance()->addListener((EventType)DESTROY, this);
	EventSystem::getInstance()->addListener((EventType)PAUSE_ANIMATIONS, this);
	EventSystem::getInstance()->addListener((EventType)SWAP_ANIMATIONS, this);
}

void Game::cleanup()
{
	delete mpWoodsSprite;
	mpWoodsSprite = nullptr;
	mSystem->cleanup();
	delete mSystem;
	mSystem = nullptr;
	delete mpInputTranslator;
	mpInputTranslator = nullptr;
	delete mpInputSystem;
	mpInputSystem = nullptr;
}

System* Game::getSystem()
{
	return mSystem;
}

void Game::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == EXIT_GAME)
	{
		exitDoloop();
	}
	else if (theEvent.getType() == CREATE)
	{
		const UnitEvent& temp = static_cast<const UnitEvent&>(theEvent);
		createNewUnit(temp.getLocation());
	}
	else if (theEvent.getType() == DESTROY)
	{
		const DestroyEvent& temp = static_cast<const DestroyEvent&>(theEvent);
		deleteUnitAtLoc(temp.getLocation());
	}
	else if (theEvent.getType() == PAUSE_ANIMATIONS)
	{
		pauseAllAnimation();
	}
	else if (theEvent.getType() == SWAP_ANIMATIONS)
	{
		swapAnimationOfLastUnit();
	}
}

void Game::createNewUnit(Vector2D loc)
{
	loc-= Vector2D(30, 30);
	vector<Animation> temp;
	temp.push_back(Animation(*mBufferManager.getBuffer(SMURF_KEY), SMURF_SPRITE_SIZE));
	temp.push_back(Animation(*mBufferManager.getBuffer(DEAN_KEY), SMURF_SPRITE_SIZE));
	mUnitManager.createUnit(temp, loc);
}

void Game::deleteUnitAtLoc(Vector2D loc)
{
	mUnitManager.deleteByPosition(loc);
}

void Game::pauseAllAnimation()
{
	mUnitManager.pausePlayAllUnits();
}

void Game::swapAnimationOfLastUnit()
{
	mUnitManager.getUnit()->swapAnimations();
}

void Game::exitDoloop()
{
	mLoopGame = false;
}
