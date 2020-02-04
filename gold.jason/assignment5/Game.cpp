#include "Game.h"
#include "GameEvent.h"
#include "EventSystem.h"

Game* Game::mpGameInstance = nullptr;

Game::Game(EventSystem* eventSys):EventListener(eventSys)
{

}

void Game::calledEvent(const Event & event)
{
	if(event.getType() == (EventType)CREATE) //CHECK THIS
	{
		Vector2D newLoc = mpSystem->getInputSys()->getMouseLocation();
		mpUnitHolder->addUnit(newLoc.getX(), newLoc.getY(), 1.0f, mSmurfVector);
		mpUnitHolder->getCurrentUnit()->addAnimations(mDeanSmurfVector);
		cout << "Added Unit" << endl;
	}
	else if(event.getType() == (EventType)DEL)
	{
		Vector2D newLocation = mpSystem->getInputSys()->getMouseLocation();
		mpUnitHolder->removeUnit(newLocation.getX(), newLocation.getY());
		cout << "Deleted Unit" << endl;
	}
	else if(event.getType() == (EventType)PAUSE)
	{
		mpUnitHolder->setAnimationAll();
		cout << "Pause Units" << endl;
	}
	else if(event.getType() == (EventType)SWAP)
	{
		mpUnitHolder->getCurrentUnit()->setAnimation();
		cout << "Swap Unit" << endl;
	}
	else if(event.getType() == (EventType)EXIT)
	{
		mShutDown = true;
		cout << "End of Line" << endl;
	}
}

Game::~Game()
{
	cleanUpGame();
}

Game * Game::getInstance()
{
	assert(mpGameInstance != nullptr);
	return mpGameInstance;
}

void Game::initInstance(EventSystem* eventSys)
{
	mpGameInstance = new Game(eventSys);
	eventSys->addListener((EventType)CREATE, mpGameInstance);
	eventSys->addListener((EventType)DEL, mpGameInstance);
	eventSys->addListener((EventType)PAUSE, mpGameInstance);
	eventSys->addListener((EventType)SWAP, mpGameInstance);
	eventSys->addListener((EventType)EXIT, mpGameInstance);
	
}

void Game::cleanUpInstance()
{
	delete mpGameInstance;
}

void Game::initGame(int dispHeight, int dispWidth)
{
	mpUnitHolder = new UnitManager();
	mpSystem = new System();
	mpTimer = new Timer;
	mpSystem->InitSystem(dispHeight, dispWidth);
	mpGraphicsBufferHolder = new GraphicsBufferManager();
	mInputTrans = new InputTranslator(getEventSystem()); //I think this is where the problem is?

	mpGraphicsBufferHolder->addBuffer(ASSET_PATH + WOODS_FILENAME, "Woods");
	mpGraphicsBufferHolder->addBuffer(ASSET_PATH + SMURFS_FILENAME, "Smurfs");
	mpGraphicsBufferHolder->addBuffer(ASSET_PATH + DEAN_SMURFS_FILENAME, "DeanSmurfs");
	//consts for smurfs
	const float SMURF_HEIGHT = mpGraphicsBufferHolder->getGraphicsBuffer("Smurfs")->getHeight() / SMURF_ROWS;
	const float SMURF_WIDTH = mpGraphicsBufferHolder->getGraphicsBuffer("Smurfs")->getWidth() / SMURF_COLS;
	//consts for unit's start location
	const float UNIT_STARTX = DISP_WIDTH / 2.0f;
	const float UNIT_STARTY = DISP_HEIGHT / 2.0f;
	//sprite vectors
	
	//filling up sprite vectors
	for (int i = 0;i < SMURF_COLS;i++)
	{
		for (int k = 0;k < SMURF_ROWS;k++)
		{
			mSmurfVector.push_back(new Sprites(SMURF_HEIGHT, SMURF_WIDTH, mpGraphicsBufferHolder->getGraphicsBuffer("Smurfs"), (k * SMURF_HEIGHT), (i * SMURF_WIDTH)));
			mDeanSmurfVector.push_back(new Sprites(SMURF_HEIGHT, SMURF_WIDTH, mpGraphicsBufferHolder->getGraphicsBuffer("DeanSmurfs"), (k * SMURF_HEIGHT), (i * SMURF_WIDTH)));
		}
	}
	mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Woods"), 0.0f, 0.0f, 0.5f);
}

void Game::cleanUpGame()
{
	mpSystem->CleanUpSystem();
	delete mpSystem;
	delete mpTimer;
	delete mpGraphicsBufferHolder;
	delete mpUnitHolder;
	delete mInputTrans;
	for(unsigned int i = 0; i < mSmurfVector.size();i++)
	{
		delete mSmurfVector[i];
	}
	for (unsigned int i = 0; i < mDeanSmurfVector.size();i++)
	{
		delete mDeanSmurfVector[i];
	}
}

void Game::doLoop()
{
	mpTimer->start();
	PerformanceTracker* pTracker = new PerformanceTracker();
	pTracker->startTracking("Draw");
	do
	{
		pTracker->clearTracker("Draw");
		pTracker->startTracking("Draw");
		mpTimer->start();

		mInputChoice = input();
		update();
		draw();

		mpTimer->sleepUntilElapsed(16.7);
		pTracker->stopTracking("Draw");
		std::cout << pTracker->getElapsedTime("Draw") << std::endl;

	} while (mShutDown == false);

	delete pTracker;
	pTracker = nullptr;
}

int Game::input()
{
	mpSystem->getInputSys()->update();
	return 0;
}

void Game::update()
{
	mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Woods"), 0.0f, 0.0f, 0.5f);
	mpUnitHolder->updateAll(FRAME_RATE);
}

void Game::draw()
{
	mpUnitHolder->drawAll();
	mpSystem->getGraphicsSystem()->flip_Display();
}

System * Game::getSystem()
{
	return mpSystem;
}
