#include "Game.h"
#include "GraphicsLib/InputSystem.h"
#include "EventListener.h"
#include "Event.h"
#include "GameListener.h"

Game* Game::mpGameInstance = nullptr;

Game::Game()
{
	
}

Game::~Game()
{
	cleanup();
}

Game* Game::getInstance()
{
	assert(mpGameInstance != nullptr);
	return mpGameInstance;
}

void Game::initInstance()
{
	if (mpGameInstance == nullptr)
	{
		mpGameInstance = new Game();
	}
}

void Game::cleanupInstance()
{
	delete mpGameInstance;
}

void Game::init(float w, float h, float t)
{
	mpPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	mTimeScale = t;

	mpGameSys = new System(w, h);

	mpBufferManager = new GraphicsBufferManager();

	mpBufferManager->addNewBuffer(WOODS_PATH, 0, 0, true);
	mpBufferManager->addNewBuffer(SMURF_PATH, 0, 0, false);
	mpBufferManager->addNewBuffer(DEAN_PATH, 0, 0, false);

	//mpWoodsBuffer = new GraphicsBuffer(WOODS_PATH.c_str());
	//mpSmurfBuffer = new GraphicsBuffer(SMURF_PATH.c_str());
	//mpDeanBuffer = new GraphicsBuffer(DEAN_PATH.c_str());

	//smurfUnit = new Unit();
	//smurfUnit->setX(350.0);
	//smurfUnit->setY(250.0);
	//smurfUnit->loadAnimation(mpSmurfBuffer, 4, 4);

	mpUnitManager = new UnitManager();

	mpEventSystem = new EventSystem();

	mpTranslator = new InputTranslator(mpEventSystem);
	
	pListener = new GameListener(mpEventSystem);
	mpEventSystem->addListener(ADD_EVENT, pListener);
	pListener1 = new GameListener(mpEventSystem);
	mpEventSystem->addListener(DELETE_EVENT, pListener1);
	pListener2 = new GameListener(mpEventSystem);
	mpEventSystem->addListener(FREEZE_EVENT, pListener2);
	pListener3 = new GameListener(mpEventSystem);
	mpEventSystem->addListener(EXIT_EVENT, pListener3);
	pListener4 = new GameListener(mpEventSystem);
	mpEventSystem->addListener(DEAN_EVENT, pListener4);



	//mpEventSystem->addListener()

	mpPerformanceTracker->stopTracking(INIT_TRACKER_NAME);

	

}

void Game::cleanup()
{
	delete mpPerformanceTracker;
	delete mpTimer;
	delete mpGameSys;
	delete mpBufferManager;

	delete mpUnitManager;

	delete pListener;
	delete pListener1;
	delete pListener2;
	delete pListener3;
	delete pListener4;
	delete mpTranslator;
	delete mpEventSystem;
}

void Game::gameLoop()
{
	do {
		mpPerformanceTracker->clearTracker("loop");
		mpPerformanceTracker->startTracking("loop");

		mpTimer->start();

		getInput();
		update();
		render();

		mpTimer->sleepUntilElapsed(mTimeScale);
		mpTimer->stop();

		mpPerformanceTracker->stopTracking("loop");
		std::cout << std::endl << "Time to loop: " << mpPerformanceTracker->getElapsedTime("loop");
	} 
	while (!mExit);
}

void Game::getInput()
{
	//get input from allegro
	mpGameSys->getInput()->checkInput();
}

void Game::update()
{
	if (mUnitUpdate)
	{
		mpUnitManager->update();
	}
}

void Game::render()
{
	mpBufferManager->draw();

	mpUnitManager->draw();

	mpGameSys->flip();
}

void Game::shouldExit()
{
	mExit = true;
}

void Game::adjustTime(float change)
{
	mTimeScale *= change;
}

//Switches smurf between normal smurf and Dean smurf
void Game::switchAnim()
{
	if (mIsDean)
	{
		mpUnitManager->getUnit(mpUnitManager->getSize()-1)->loadAnimation(mpBufferManager->getBuffer(1), 4, 4);
	}
	else
	{
		mpUnitManager->getUnit(mpUnitManager->getSize()-1)->loadAnimation(mpBufferManager->getBuffer(2), 4, 4);
	}

	mIsDean = !mIsDean;
}

void Game::addSmurf(float x, float y)
{
	mpUnitManager->addNewUnit(mpBufferManager->getBuffer(1), 4, 4);

	mpUnitManager->setX(x, mpUnitManager->getSize() - 1);
	mpUnitManager->setY(y, mpUnitManager->getSize() - 1);
}

void Game::removeUnitAt(float x, float y)
{
	mpUnitManager->removeUnitsAt(x, y);
}

void Game::enableUnitUpdating()
{
	mUnitUpdate = !mUnitUpdate;
}

void Game::fireEvent(const Event& theEvent)
{
	mpEventSystem->fireEvent(theEvent);
}

void Game::addListener(EventType type, EventListener* pListener)
{
	mpEventSystem->addListener(type, pListener);
}