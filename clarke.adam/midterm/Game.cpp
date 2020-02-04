#include "Game.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "SegmentDestroyedEvent.h"

Game* Game::mpsGame = nullptr;

Game::Game()
{
	mpGameData = new GameData();
	mpSystem = new System();
	mpTimer = new Timer();
	mpPerformanceTracker = new PerformanceTracker();
	mpInputTranslator = new InputTranslator();
	mpCollisionSystem = new CollisionSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpHudManager = new HudManager();
	mpMushroomUnitManager = new MushroomUnitManager();
	mpCentipedeManager = new CentipedeManager();
}

Game::~Game()
{
	delete mpCentipedeManager;
	delete mpMushroomUnitManager;
	delete mpHudManager;
	delete mpGraphicsBufferManager;
	delete mpCollisionSystem;
	delete mpInputTranslator;
	delete mpPerformanceTracker;
	delete mpTimer;
	delete mpSystem;
	delete mpGameData;

	Game::cleanup();
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

void Game::init(const std::string& configFilepath)
{
	mIsInitted = true;

	mpGameData->read(configFilepath);
	mpSystem->init(mpGameData->getDisplayDimensions());
	mpInputTranslator->init();
	mpHudManager->init();
	mpCentipedeManager->init();
	mpMushroomUnitManager->init();
	mpPlayerUnit = new PlayerUnit();
	mpFont = new Font(mpGameData->getAssetPath() + mpGameData->getFontFilename(),
		mpGameData->getMenuFontSize());
	mGameState = MENU;
	mShouldExit = false;

	auto eventSystem = EventSystem::getInstance();
	eventSystem->addListener(EventType(MUSHROOM_DESTROYED_EVENT), this);
	eventSystem->addListener(EventType(SEGMENT_DESTROYED_EVENT), this);
	eventSystem->addListener(EventType(CENTIPEDE_KILLED_EVENT), this);
	eventSystem->addListener(EventType(PLAYER_LOSE_LIFE_EVENT), this);
	eventSystem->addListener(EventType(PLAY_EVENT), this);
	eventSystem->addListener(EventType(EXIT_GAME_EVENT), this);

	mMsPerFrame = 1000 / mpGameData->getTargetFrameRate();
	mpTimer->start();
}

void Game::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	EventListener::cleanup();
	delete mpFont;
	delete mpPlayerUnit;
	mpMushroomUnitManager->cleanup();
	mpCentipedeManager->cleanup();
	mpHudManager->cleanup();
	mpGraphicsBufferManager->clear();
	mpInputTranslator->cleanup();
	mpSystem->cleanup();

}

void Game::doLoop()
{
	while (!mShouldExit)
	{
		mpPerformanceTracker->clearTracker(LOOP_TRACKER);
		mpPerformanceTracker->startTracking(LOOP_TRACKER);

		// time this loop
		const auto curTime = mpTimer->getElapsedTime();

		physicsUpdate(curTime);
		update(curTime);
		render();

		// sleep until mMsPerFrame since loop start to run at target fps
		mpTimer->sleepUntilElapsed(curTime + mMsPerFrame);

		mpPerformanceTracker->stopTracking(LOOP_TRACKER);
		mpHudManager->setFps(1000.0f / mpPerformanceTracker->getElapsedTime(LOOP_TRACKER));
	}
}

void Game::handleEvent(const Event& theEvent)
{
	const auto eventType = GameEventType(theEvent.getType());
	switch (eventType)
	{
	case EXIT_GAME_EVENT:
	{
		exitGame();
		break;
	}
	case PLAY_EVENT:
	{
		if (mGameState == MENU || mGameState == END)
		{
			initLevel();
		}
		break;
	}
	case MUSHROOM_DESTROYED_EVENT:
	{
		mScore += mpGameData->getMushroomDestroyPoints();
		mpHudManager->setScore(mScore);
		break;
	}
	case SEGMENT_DESTROYED_EVENT:
	{
		auto segmentDestroyedEvent = dynamic_cast<const SegmentDestroyedEvent&>(theEvent);
		mScore += segmentDestroyedEvent.getPoints();
		mpHudManager->setScore(mScore);
		break;
	}
	case CENTIPEDE_KILLED_EVENT:
	{
		mLevel++;
		mpHudManager->setLevel(mLevel);
		respawn(true);
		break;
	}
	case PLAYER_LOSE_LIFE_EVENT:
	{
		mPlayerLives--;
		mpHudManager->setLives(mPlayerLives);
		if (mPlayerLives <= 0)
		{
			gameOver();
		}
		else
		{
			respawn(false);
		}
		break;
	}
	}

	if (mScore > mPointsForExtraLife)
	{
		mPlayerLives++;
		mPointsForExtraLife += mPointsForExtraLife;
		mpHudManager->setLives(mPlayerLives);
	}
}

void Game::physicsUpdate(float curTime)
{
	if (mGameState != LEVEL) return;

	mpMushroomUnitManager->physicsUpdate(curTime);
	mpCentipedeManager->physicsUpdate(curTime);
	mpPlayerUnit->physicsUpdate(curTime);
}

void Game::update(float curTime)
{
	mpSystem->update(curTime);
	mpInputTranslator->update(curTime);

	if (mGameState == LEVEL)
	{
		mpCentipedeManager->update(curTime);
		mpMushroomUnitManager->update(curTime);
		mpPlayerUnit->update(curTime);
	}
}

void Game::render()
{
	mpSystem->getGraphicsSystem()->clearToColor(mpGameData->getBackgroundColor());

	switch (mGameState)
	{
	case MENU:
	{
		getSystem()->getGraphicsSystem()->writeText(mpGameData->getMenuTextLoc(), *mpFont,
			mpGameData->getMenuFontColor(), "CENTIPEDE press space to play");
		break;
	}
	case LEVEL:
	{
		mpMushroomUnitManager->draw();
		mpPlayerUnit->draw();
		mpCentipedeManager->draw();
		mpHudManager->draw();
		break;
	}
	case END:
	{
		getSystem()->getGraphicsSystem()->writeText(mpGameData->getEndTextLoc(), *mpFont,
			mpGameData->getMenuFontColor(), "GAME OVER. SCORE: " + std::to_string(mScore));
		getSystem()->getGraphicsSystem()->writeText(mpGameData->getPlayAgainTextLoc(), *mpFont,
			mpGameData->getMenuFontColor(), "press SPACE to play again");
		break;
	}
	}

	// flip backbuffer to display
	mpSystem->getGraphicsSystem()->flip();
}

void Game::exitGame()
{
	mShouldExit = true;
}

void Game::initLevel()
{
	mGameState = LEVEL;
	mPlayerLives = mpGameData->getInitPlayerLives();
	mpHudManager->setLives(mPlayerLives);
	mScore = 0;
	mpHudManager->setScore(mScore);
	mLevel = 1;
	mpHudManager->setLevel(mLevel);
	mPointsForExtraLife = mpGameData->getPointsForExtraLife();
	mpCentipedeManager->reset();
	mpMushroomUnitManager->reset();
	respawn(false);
}

void Game::respawn(bool doIncrementSpeed)
{
	mpCentipedeManager->respawn(doIncrementSpeed);
	mpPlayerUnit->respawn();
}

void Game::gameOver()
{
	mGameState = END;
}
