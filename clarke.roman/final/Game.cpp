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
	mpTimer = new Timer();
	mpPerformanceTracker = new PerformanceTracker();
}

Game::~Game()
{
	Game::cleanup();

	delete mpPlayerUnit;
	delete mpFont;
	delete mpPerformanceTracker;
	delete mpTimer;
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

void Game::init(const Vector2D & displayDimensions, float targetFrameRate)
{
	mIsInitted = true;

	mSceneIndex = 0;

	auto eventSystem = EventSystem::getInstance();
	eventSystem->addListener(EventType(EXIT_GAME_EVENT), this);
	eventSystem->addListener(EventType(PLAYER_SWAP_DIR_EVENT), this);

	mpInputTranslator->init();
	mpSystem->init(displayDimensions);

	mMsPerFrame = 1000 / targetFrameRate;
	mShouldExit = false;
	// start timer used to measure loop time
	mpTimer->start();

	//import font
	mpFont = new Font(ASSET_PATH + FONT_FILENAME, 30);

	// woods image buffer
	mpGraphicsBufferManager->createGraphicsBuffer(WOODS_BUFFER_KEY, ASSET_PATH + WOODS_FILENAME);
	// sprite of entire woods buffer
	const auto woodsBuffer = mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY);
	mpWoodsSprite = new Sprite(woodsBuffer, Vector2D(0, 0), woodsBuffer->getDimensions());
	// set woods scale to match display size
	mWoodsScale = Vector2D(mpSystem->getGraphicsSystem()->getDisplayWidth() / mpWoodsSprite->getDimensions().getX(),
		mpSystem->getGraphicsSystem()->getDisplayHeight() / mpWoodsSprite->getDimensions().getY());


	mpGraphicsBufferManager->createGraphicsBuffer(mPlayerSkateBufferKey,
		ASSET_PATH + mPlayerSkateFilename);
	Animation playerSkateAnim(mpGraphicsBufferManager->getGraphicsBuffer(mPlayerSkateBufferKey),
		smurfSpriteDim, smurfAnimSpeed, true);
	std::map<std::string, Animation> playerSkateAnims
	{
		{ mPlayerSkateBufferKey, playerSkateAnim },
	};
	mpPlayerUnit = new PlayerUnit(playerSkateAnims, Vector2D(400, 300), smurfScale);
	// set new smurf unit's initial animation to regular smurf
	mpPlayerUnit->setAnimation(mPlayerSkateBufferKey);
}

void Game::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	delete mpWoodsSprite;

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

void Game::handleEvent(const Event & theEvent)
{
	const auto eventType = GameEventType(theEvent.getType());
	if (eventType == EXIT_GAME_EVENT)
	{
		exitGame();
	}
	else if (eventType == PLAYER_SWAP_DIR_EVENT && mSceneIndex ==0)
	{
		mSceneIndex = 1;
	}
}

void Game::update(float curTime)
{
	mpSystem->update(curTime);

	switch (mSceneIndex)
	{
	case 0: //Main Menu
		break;
	case 1://Main Level
		mpPlayerUnit->update(curTime);
		break;
	}
}

void Game::render()
{
	switch (mSceneIndex)
	{
	case 0: //Main Menu

		mpSystem->getGraphicsSystem()->writeText(Vector2D(100, 100), *mpFont, PINK, "SKATER HEAVEN");
		mpSystem->getGraphicsSystem()->writeText(Vector2D(200, 200), *mpFont, PINK, "Spress space or click to start");
		break;
	case 1://Main Level
		mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, mWoodsScale);
		mpPlayerUnit->draw();
		break;
	}



	// flip backbuffer to display
	mpSystem->getGraphicsSystem()->flip();
}

void Game::exitGame()
{
	mShouldExit = true;
}

