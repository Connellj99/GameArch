#include "Game.h"
#include "EventSystem.h"
#include "GameEvent.h"
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

	mpInputTranslator->init();
	mpSystem->init(displayDimensions);

	mMsPerFrame = 1000 / targetFrameRate;
	mShouldExit = false;
	// start timer used to measure loop time
	mpTimer->start();

	// woods image buffer
	mpGraphicsBufferManager->createGraphicsBuffer(WOODS_BUFFER_KEY, ASSET_PATH + WOODS_FILENAME);
	// sprite of entire woods buffer
	const auto woodsBuffer = mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY);
	mpWoodsSprite = new Sprite(woodsBuffer, Vector2D(0, 0), woodsBuffer->getDimensions());
	// set woods scale to match display size
	mWoodsScale = Vector2D(mpSystem->getGraphicsSystem()->getDisplayWidth() / mpWoodsSprite->getDimensions().getX(),
		mpSystem->getGraphicsSystem()->getDisplayHeight() / mpWoodsSprite->getDimensions().getY());

	mpUnitManager->init();
}

void Game::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	delete mpWoodsSprite;

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
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, mWoodsScale);

	// draw all smurfs
	mpUnitManager->draw();

	// flip backbuffer to display
	mpSystem->getGraphicsSystem()->flip();
}

void Game::exitGame()
{
	mShouldExit = true;
}

