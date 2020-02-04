/*
Conner Root
EGP 310 - 01
*/

#include "Game.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "MouseClickEvent.h"
#include "KeyDownEvent.h"
#include "SpawnEvent.h"
#include "DeleteEvent.h"
#include "ChangeSpeedEvent.h"

Game* Game::mpsGameObj = NULL;

// Constructor
Game::Game()
{
}

// Instance
void Game::initInstance()
{
	if (mpsGameObj == NULL)
	{
		mpsGameObj = new Game();
	}
}

Game* Game::getInstance()
{
	return mpsGameObj;
}

void Game::cleanupInstance()
{
	if (mpsGameObj != NULL)
	{
		mpsGameObj->cleanup();
		delete mpsGameObj;
		mpsGameObj = NULL;
	}
}

// Init / Cleanup
void Game::init(int w, int h, float fR = 60)
{
	if (!mInited)
	{
		mFrameRate = fR;
		mTimePerFrame = 1000.0 / fR;

		// Create and init system
		mpSystem = new System();
		mpSystem->init(w, h);

		// Create and populate buffer manager
		mpBufferManager = new GraphicsBufferManager();
		mpBufferManager->addBuffer(ASSET_PATH + BACKGROUND_FILENAME);
		mpBufferManager->addBuffer(ASSET_PATH + SMURFS_FILENAME);
		mpBufferManager->addBuffer(ASSET_PATH + DEAN_FILENAME);

		// Create background sprite
		mpBackground = new Sprite(mpBufferManager->getBuffer(ASSET_PATH + BACKGROUND_FILENAME), 0, 0, mpBufferManager->getBuffer(ASSET_PATH + BACKGROUND_FILENAME)->getWidth(), mpBufferManager->getBuffer(ASSET_PATH + BACKGROUND_FILENAME)->getHeight());

		// Create and populate unit manager
		mpUnitManager = new UnitManager();
		mpUnitManager->addAnim(mpBufferManager->getBuffer(ASSET_PATH + SMURFS_FILENAME), 60, 60, 1.0, true);
		mpUnitManager->addAnim(mpBufferManager->getBuffer(ASSET_PATH + DEAN_FILENAME), 60, 60, 1.0, true);

		mpTimer = new Timer();

		// Init translator
		mpInputTranslator = new InputTranslator();
		mpInputTranslator->init();

		// Add Listeners
		EventSystem::getInstance()->addListener(EventType(SPAWN_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(DELETE_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(EXIT_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(SPEED_CHANGE_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(PAUSE_ANIM_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(TOGGLE_ANIM_EVENT), this);

		mInited = true;
	}
}

void Game::cleanup() 
{
	if (mInited)
	{
		delete mpBufferManager;
		delete mpUnitManager;
		delete mpBackground;
		delete mpTimer;
		delete mpSystem;
		mpInputTranslator->cleanup();
		delete mpInputTranslator;
		
		mInited = false;
	}
}

// Game Loop
void Game::gameLoop()
{
	PerformanceTracker* pPerfomanceTracker = new PerformanceTracker();
	float sum = 0, cnt = 0;

	while (getExitState())
	{
		pPerfomanceTracker->clearTracker("loop");
		pPerfomanceTracker->startTracking("loop");
		mpTimer->start();

		//getInput();
		update();
		drawScene();

		mpTimer->sleepUntilElapsed(trunc(mTimePerFrame*100)/100);
		pPerfomanceTracker->stopTracking("loop");
		cout << endl << "loop time: " << pPerfomanceTracker->getElapsedTime("loop");
		sum += pPerfomanceTracker->getElapsedTime("loop");
		cnt++;
	}

	cout << "\n\nAverage loop time: " << (sum / cnt) << endl
		<< "Average Framrate: " << 1000 / (sum / cnt) << endl << endl;

	delete pPerfomanceTracker;
}
// Events
void Game::handleEvent(const Event& evt)
{
	switch (GameEventType(evt.getType()))
	{
	case SPAWN_EVENT:
	{
		auto spawnEvt = dynamic_cast<const SpawnEvent&>(evt);
		spawnUnit(spawnEvt.getXPos(), spawnEvt.getYPos());
		break;
	}
	case DELETE_EVENT:
	{
		auto deleteEvt = dynamic_cast<const DeleteEvent&>(evt);
		deleteUnit(deleteEvt.getXPos(), deleteEvt.getYPos());
		break;
	}
	case EXIT_EVENT:
	{
		mShouldExit = true;
		break;
	}
	case SPEED_CHANGE_EVENT:
	{
		auto changeEvt = dynamic_cast<const ChangeSpeedEvent&>(evt);
		if (changeEvt.getChange() == 1)
			speedUpAnimation();
		else if (changeEvt.getChange() == -1)
			slowDownAnimation();
		break;
	}
	case PAUSE_ANIM_EVENT:
	{
		togglePause();
		break;
	}
	case TOGGLE_ANIM_EVENT:
	{
		toggleAnimation();
		break;
	}
	default:
		break;
	}
}

// Game functions
void Game::spawnUnit(int x, int y)
{
	mpUnitManager->addUnit(x, y);
}
void Game::deleteUnit(int x, int y)
{
	mpUnitManager->deleteUnit(x, y);
}
void Game::speedUpAnimation()
{
	mpUnitManager->getUnit()->getAnimation()->speedUp();
}
void Game::slowDownAnimation()
{
	mpUnitManager->getUnit()->getAnimation()->slowDown();
}
void Game::togglePause()
{
	mpUnitManager->toggleAnimationPause();
}
void Game::toggleAnimation()
{
	mpUnitManager->switchAnimation();
}

void Game::getInput()
{
	/*
	if (mpSystem->checkKeyDown(ESC))
		mShouldExit = true;
	*/
}

void Game::update()
{
	mpUnitManager->updateUnits();
	mpSystem->getInputSystem()->update();
}

void Game::drawScene()
{
	mpSystem->getGraphicsSystem()->draw(0, 0, mpBackground, 1.0);
	mpUnitManager->drawUnits();
	mpSystem->getGraphicsSystem()->flipDisplay();
}

// Destructor
Game::~Game()
{
	if (mInited)
		cleanup();
}