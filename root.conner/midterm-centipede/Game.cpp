/*
Conner Root
EGP 310 - 01
*/

#include <fstream>

#include "Game.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "MouseClickEvent.h"
#include "MovePlayerEvent.h"
#include "KeyDownEvent.h"
#include "SpawnEvent.h"
#include "DeleteEvent.h"
#include "ChangeSpeedEvent.h"
#include "ScoreEvent.h"

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
void Game::init()
{
	if (!mInited)
	{
		// Ifstream variable
		ifstream inFile("gameSettings.txt");

		// Get game settings
		inFile >> mDispWidth;
		inFile >> mDispHeight;
		inFile >> mFrameRate;

		mTimePerFrame = 1000.0 / mFrameRate;

		// Create and init system
		mpSystem = new System();
		mpSystem->init(mDispWidth, mDispHeight);

		// Create buffer and unit manager
		mpBufferManager = new GraphicsBufferManager();
		mpUnitManager = new UnitManager();

		// Create black background
		mpBufferManager->addBuffer("Background", mDispWidth, mDispHeight);
		mpBackground = new Sprite(mpBufferManager->getBuffer("Background"), 0, 0, mDispWidth, mDispHeight);

		// Create buffers and animations
		string assetPath;
		inFile >> assetPath;

		int numFiles;
		inFile >> numFiles;
		
		for (int i = 0; i < numFiles; i++)
		{
			string tempFilename;
			int w, h;

			inFile >> tempFilename;
			inFile >> w >> h;

			mpBufferManager->addBuffer(assetPath + tempFilename);
			mpUnitManager->addAnim(mpBufferManager->getBuffer(assetPath + tempFilename), w, h, 1.0, true);
		}
		
		// Init Unit Manager
		mpUnitManager->init(mDispWidth, mDispHeight);

		// Create Timer
		mpTimer = new Timer();

		// Create font
		mpFontCour = new Font();
		string fontFileName;
		int size;
		inFile >> fontFileName;
		inFile >> size;
		mpFontCour->init(assetPath + fontFileName, size);

		// Create color
		mFontColor = Color(255, 15, 5);

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
		EventSystem::getInstance()->addListener(EventType(MOVE_PLAYER_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(SCORE_EVENT), this);
		EventSystem::getInstance()->addListener(EventType(DEATH_EVENT), this);

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
		delete mpFontCour;
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

		
		update();
		drawScene();

		mpTimer->sleepUntilElapsed(mTimePerFrame);
		pPerfomanceTracker->stopTracking("loop");
		cout << endl << "loop time: " << pPerfomanceTracker->getElapsedTime("loop");
		sum += pPerfomanceTracker->getElapsedTime("loop");
		cnt++;
		mCurrFPS = 1000 / pPerfomanceTracker->getElapsedTime("loop");
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
		mpUnitManager->shoot();
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
		mpUnitManager->increaseDifficulty(changeEvt.getChange());
		break;
	}
	case PAUSE_ANIM_EVENT:
	{
		startGame();
		break;
	}
	case MOVE_PLAYER_EVENT:
	{
		auto moveEvt = dynamic_cast<const MovePlayerEvent&>(evt);
		movePlayer(moveEvt.getXPos(), moveEvt.getYPos());
		break;
	}
	case SCORE_EVENT:
	{
		auto scoreEvt = dynamic_cast<const ScoreEvent&>(evt);
		addToScore(scoreEvt.getFlag());
		break;
	}
	case DEATH_EVENT:
	{
		killPlayer();
		break;
	}
	default:
		break;
	}
}

// Game functions
void Game::addToScore(char f)
{
	switch (f)
	{
	case 'h':
		mScore += 100;
		break;
	case 'b':
		mScore += 10;
		break;
	case 'm':
		mScore += 1;
		break;
	default:
		break;
	}

	if (mScore - (12000 * mExtraLives) >= 12000)
	{
		mLives++;
		mExtraLives++;
	}
}
void Game::deleteUnit(int x, int y)
{
	mpUnitManager->deleteUnit(x, y);
}
void Game::movePlayer(int x, int y)
{
	// Set max y value
	if (y < 600)
		y = 600;

	mpUnitManager->getPlayer()->setLocation(x, y);
}
void Game::killPlayer()
{
	mLives--;
	mpUnitManager->deleteAllUnits();
	mpUnitManager->setUnits();

	if (mLives <= 0)
		endGame();
}
void Game::startGame()
{
	if (!mPlaying)
	{
		mLives = 3;
		mScore = 0;
		mPlaying = true;
		mEnded = false;
	}
}
void Game::endGame()
{
	mEnded = true;
	mpUnitManager->resetAllUnitStates();
	mPlaying = false;
}

/*
void Game::spawnUnit(int x, int y)
{
}
void Game::speedUpAnimation()
{
	mpUnitManager->getUnit()->getAnimation()->speedUp();
}
void Game::slowDownAnimation()
{
	mpUnitManager->getUnit()->getAnimation()->slowDown();
}
*/

void Game::update()
{
	if (mPlaying)
		mpUnitManager->updateUnits();

	mpSystem->getInputSystem()->update();
}

void Game::drawScene()
{
	mpSystem->getGraphicsSystem()->draw(0, 0, mpBackground, 1.0);

	string strTop = "LIVES: " + to_string(mLives) + " | SCORE: " + to_string(mScore) + "  | FPS: " + to_string(mCurrFPS);
	mpSystem->getGraphicsSystem()->writeText(0, 0, mpFontCour, mFontColor, strTop);

	if (mPlaying)
	{
		mpUnitManager->drawUnits();
	}
	else
	{
		if (mEnded)
		{
			string strEnd = "YOU DIED!";
			mpSystem->getGraphicsSystem()->writeText(mDispWidth / 2.7, mDispHeight / 2 - 25, mpFontCour, mFontColor, strEnd);
		}

		string strStart = "PRESS SPACE TO START";
		mpSystem->getGraphicsSystem()->writeText(mDispWidth / 3.2, mDispHeight / 2.25, mpFontCour, mFontColor, strStart);
	}

	mpSystem->getGraphicsSystem()->flipDisplay();
}

// Destructor
Game::~Game()
{
	if (mInited)
		cleanup();
}