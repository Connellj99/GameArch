/*
Conner Root
EGP 310 - 01
*/

#include "Game.h"

Game* Game::mpsGameObj = NULL;

// Constructor
Game::Game()
{
}

// Get Instance
void Game::initInstance()
{
	if (mpsGameObj == NULL)
	{
		mpsGameObj = new Game;
	}
}

Game* Game::getInstance()
{
	return mpsGameObj;
}

// Init / Cleanup
void Game::init(int w, int h, float fR = 60)
{
	if (!mInited)
	{
		mFrameRate = fR;
		mTimePerFrame = 1000.0 / fR;

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

		mInited = true;
	}
}

void Game::cleanup() 
{
	if (mInited)
	{
		delete mpSystem;
		delete mpUnitManager;
		delete mpBackground;
		delete mpBufferManager;
		delete mpTimer;
		
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

		getInput();
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

void Game::getInput()
{
	mMouseState = mpSystem->checkMouseDown();
	if (mMouseState.lClicked)
		mpUnitManager->addUnit(mMouseState.xPos, mMouseState.yPos);

	if(mMouseState.rClicked)
		mpUnitManager->deleteUnit(mMouseState.xPos, mMouseState.yPos);

	if (mpSystem->checkKeyDown(F))
	{
		mpUnitManager->getUnit()->getAnimation()->speedUp();
	}

	if (mpSystem->checkKeyDown(S))
	{
		mpUnitManager->getUnit()->getAnimation()->slowDown();
	}

	if(mpSystem->checkKeyDown(ENTER))
	{
		mpUnitManager->switchAnimation();
	}

	if (mpSystem->checkKeyDown(SPACE))
	{
		mpUnitManager->toggleAnimationPause();
	}

	if (mpSystem->checkKeyDown(ESC))
		mShouldExit = true;
}

void Game::update()
{
	mpUnitManager->updateUnits();
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
	cleanup();
}