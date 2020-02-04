#include "Game.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "InputTranslator.h"
#include "InitSmurfEvent.h"
#include "DestroySmurfEvent.h"

Game* Game::mpsGame = nullptr;

Game::Game()
{
	mpInputTranslator = new InputTranslator();
	mpSystem = new System();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager(mpGraphicsBufferManager);
	mpTimer = new Timer();
	mpPerformanceTracker = new PerformanceTracker();
}

Game::~Game()
{
	Game::cleanup();

	delete mpPerformanceTracker;
	delete mpTimer;
	delete mpUnitManager;
	delete mpGraphicsBufferManager;
	delete mpSystem;
	delete mpInputTranslator;
}

Game* Game::getInstance()
{
	assert(mpsGame != nullptr);
	return mpsGame;
}

void Game::initInstance()
{
	if (mpsGame == nullptr)
	{
		mpsGame = new Game();
	}
}

void Game::cleanupInstance()
{
	delete mpsGame;
}

void Game::init(const Vector2D& displayDimensions, float targetFrameRate)
{
	mIsInitted = true;

	auto eventSystem = EventSystem::getInstance();
	eventSystem->addListener(EventType(EXIT_GAME_EVENT), this);
	EventSystem::getInstance()->addListener((EventType)DESTROY_FOOD, this);
	EventSystem::getInstance()->addListener((EventType)CREATE_FOOD, this);
	EventSystem::getInstance()->addListener((EventType)CREATE_WALL, this);

	EventSystem::getInstance()->addListener((EventType)MOVELEFT, this);
	EventSystem::getInstance()->addListener((EventType)MOVERIGHT, this);
	EventSystem::getInstance()->addListener((EventType)MOVEUP, this);
	EventSystem::getInstance()->addListener((EventType)MOVEDOWN, this);

	mpInputTranslator->init();
	mpSystem->init(displayDimensions);

	mMsPerFrame = 1000 / targetFrameRate;
	mShouldExit = false;
	// start timer used to measure loop time
	mpTimer->start();
	//asset buffers
	mpGraphicsBufferManager->createGraphicsBuffer(FOOD_BUFFER_KEY,ASSET_PATH + FOOD_FILENAME);
	mpGraphicsBufferManager->createGraphicsBuffer(SNAKE_BUFFER_KEY, ASSET_PATH + SNAKE_FILENAME);
	mpGraphicsBufferManager->createGraphicsBuffer(WALL_BUFFER_KEY, ASSET_PATH + WALL_FILENAME);

	// background image buffer
	mpGraphicsBufferManager->createGraphicsBuffer(BACKGROUND_BUFFER_KEY, ASSET_PATH + BACKGROUND_FILENAME);
	// sprite of entire background buffer
	const auto backgrBuffer = mpGraphicsBufferManager->getGraphicsBuffer(BACKGROUND_BUFFER_KEY);
	mpBackgroundSprite = new Sprite(backgrBuffer, Vector2D(0, 0), backgrBuffer->getDimensions());
	// set background scale to match display size
	mBackgroundScale = Vector2D(mpSystem->getGraphicsSystem()->getDisplayWidth() / mpBackgroundSprite->getDimensions().getX(),
		mpSystem->getGraphicsSystem()->getDisplayHeight() / mpBackgroundSprite->getDimensions().getY());

	mpUnitManager->init();
}

void Game::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	delete mpBackgroundSprite;

	mpUnitManager->cleanup();
	mpGraphicsBufferManager->clear();
	mpSystem->cleanup();
	mpInputTranslator->cleanup();

	EventListener::cleanup();
}

void Game::doLoop()
{
	while (!mShouldExit)
	{
		mpPerformanceTracker->clearTracker(LOOP_TRACKER);
		mpPerformanceTracker->startTracking(LOOP_TRACKER);

		// time this loop
		const auto curTime = mpTimer->getElapsedTime();

		update(curTime);
		render();

		// sleep until mMsPerFrame since loop start to run at target fps
		mpTimer->sleepUntilElapsed(curTime + mMsPerFrame);

		mpPerformanceTracker->stopTracking(LOOP_TRACKER);
		std::cout << "loop time: " << mpPerformanceTracker->getElapsedTime(LOOP_TRACKER) << " ms" << std::endl;
	}
}

void Game::handleEvent(const Event& theEvent)
{
	if (GameEventType(theEvent.getType()) == EXIT_GAME_EVENT)
	{
		exitGame();
	}
	else if (theEvent.getType() == UP)
	{

	}
	else if (theEvent.getType() == DOWN)
	{

	}
	else if (theEvent.getType() == LEFT)
	{

	}
	else if (theEvent.getType() == RIGHT)
	{

	}
	else if (theEvent.getType() == CREATE_FOOD)
	{
		spawnFood();
	}
	else if (theEvent.getType() == DESTROY_FOOD)
	{

	}
	else if (GameEventType(theEvent.getType()) == CREATE_WALL)
	{
		std::cout << "yeet" << std::endl;
		spawnWall();
	}
	
}

void Game::update(float curTime)
{
	mpSystem->update(curTime);

	// update all smurfs' animations
	mpUnitManager->update(curTime);
}

void Game::render()
{
	// draw scaled woods background to backbuffer
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpBackgroundSprite, mBackgroundScale);

	// draw all smurfs
	mpUnitManager->draw();

	// flip backbuffer to display
	mpSystem->getGraphicsSystem()->flip();
}

void Game::checkFood()
{
	if (mpFoodTimer->getElapsedTime() >= mFoodTime)
	{
		mpFoodTimer->start();
		spawnFood();
	}
}

void Game::spawnFood()
{
	Vector2D loc = Vector2D(rand() % 600, rand() % 600);
	mpUnitManager->createNewUnit(FOOD_BUFFER_KEY,loc);

}

void Game::spawnWall()
{
	for (int i = 50; i < 400; i += 50)
	{
		Vector2D loc = Vector2D(100, i);
		//mpUnitManager->createNewUnit(WALL_BUFFER_KEY, loc);
	}
}

void Game::exitGame()
{
	mShouldExit = true;
}

