#include "Game.h"
#include "System.h"
#include "GraphicsBuffer.h"
#include "GBufferManager.h"

//Deanlib
#include "Timer.h"
#include "PerformanceTracker.h"
//Events
#include "Event.h" 
#include "GameEvent.h"
#include "ExitGame.h"
#include "InputSystem.h"
#include "EventSystem.h"
//Milipede
#include "HUD.h"
#include "FileReader.h"
#include "Font.h"

Game * Game::mpGameInstance = nullptr;

const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string DEANS = "dean_sprites.png";
const string SMURFS = "smurf_sprites.png";


using namespace std;

Game* gpGame = nullptr;

Game::Game(double fps, EventSystem* pEventSystem)		
	:EventListener(pEventSystem)
{
	mTargetTime = fps;
	pEventSystem->addListener((EventType)FIRE, this);
	pEventSystem->addListener((EventType)OPTIONS, this);
	pEventSystem->addListener((EventType)DIFFICULTY, this);
	pEventSystem->addListener((EventType)LOAD_GAME, this);
	pEventSystem->addListener((EventType)START_GAME, this);
	pEventSystem->addListener((EventType)EXIT_GAME, this);
}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == FIRE) 
	{	
		
	}
	else if (theEvent.getType() == EXIT_GAME)
	{
		//Exit the game loop
		mShouldRunLoop = false;
	}
	else if (theEvent.getType() == OPTIONS)
	{
		mState = 2;
	}
	else if (theEvent.getType() == DIFFICULTY)
	{
		mState = 3;
	}
	else if (theEvent.getType() == LOAD_GAME)
	{
		std::cout << "Loading Game ..." << endl;
		mState = 4;
	}
	else if (theEvent.getType() == START_GAME)
	{
		mState = 4;
	}

}

void Game::initGame(int screenX, int screenY, EventSystem* eventSystem)
{
	//Init system (including screen size + FPS)
	//Have system init GraphicsLib
	
	mDisplayX = screenX;
	mDisplayY = screenY;
	mState = 1;


	mpGameSystem = new System(mDisplayY, mDisplayX);
	mpBufferManager = new GBufferManager();
	
	mpGameSystem->initSystem();

	mpInputSystem = new InputSystem();
	mpInputSystem->init(mpGameSystem, eventSystem);

	mpFont = new Font(FileReader::getInstance()->getPath(), FileReader::getInstance()->getFont(), FileReader::getInstance()->getTextSize());
	mpSystemFont = new Font(FileReader::getInstance()->getPath(), FileReader::getInstance()->getFont(), 50);

	mpBufferManager->createNewBuffer("BG", mDisplayX, mDisplayY, 0, 0, 0);
	mpGameBackground = new Sprite(mpBufferManager->getBuffer("BG"),0, 0, mDisplayX, mDisplayY);

}

void Game::cleanupGame()
{
	delete mpGameBackground;
	delete mpSystemFont;
	delete mpFont;
	
	//delete mpplayer

	delete mpInputSystem;
	//call system cleanup
	
	delete mpBufferManager;
	
	delete mpGameSystem;
}

void Game::runGameLoop()
{
	mShouldRunLoop = true;
	srand(time(NULL));
	PerformanceTracker loopTracker;
	Timer mGameTimer;

	

		while (mShouldRunLoop)
		{

			loopTracker.clearTracker("GameLoop");
			loopTracker.startTracking("GameLoop");

			mGameTimer.start();


			// Process user input
			processInput();

			//Update
			update();

			//Draw 
			draw();

			//Display picture
			

			//get current time again
			double postTime = mGameTimer.getElapsedTime();

			//sleep time = target time - elapsed time
			double sleepTime = mTargetTime;

			//sleep for (sleep time) - al_rest
			mGameTimer.sleepUntilElapsed(sleepTime);

			loopTracker.stopTracking("GameLoop");
			mFPSCount = 1000/loopTracker.getElapsedTime("GameLoop"); 

		}


	
}

void Game::processInput()
{
	mpInputSystem->update();

}

void Game::update()
{

}

void Game::draw()
{

	switch (mState)
	{
	case 1:

		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);
		
		mpGameSystem->getDisplay()->writeText((mDisplayX/2), (mDisplayY/2) - 300, mpSystemFont, 255, 255, 255, "Milipede", 1);
		mpGameSystem->getDisplay()->writeText((mDisplayX / 2), mDisplayY / 2, mpSystemFont, 255, 255, 255, "[L]oad Game", 1);
		mpGameSystem->getDisplay()->writeText((mDisplayX / 2), (mDisplayY / 2) - 100, mpSystemFont, 255, 255, 255, "[S]tart new Game", 1);
		mpGameSystem->getDisplay()->writeText((mDisplayX / 2), (mDisplayY / 2) - 200, mpSystemFont, 255, 255, 255, "[O]ptions", 1);



		mpGameSystem->getDisplay()->flipDispaly();
		break;

	case 2:
		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);

		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) - 300, mpSystemFont, 255, 255, 255, "Options", 1);
		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) - 100, mpSystemFont, 255, 255, 255, "[L]anguage", 1);
		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) - 000, mpSystemFont, 255, 255, 255, "[D]ifficulty", 1);
		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) + 100, mpSystemFont, 255, 255, 255, "Music: [N] = On | [M] = Off", 1);




		mpGameSystem->getDisplay()->flipDispaly();
		break;

	case 3:
		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);

		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) - 300, mpSystemFont, 255, 255, 255, "Language", 1);
		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) - 100, mpSystemFont, 255, 255, 255, "[1]: English", 1);
		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) - 000, mpSystemFont, 255, 255, 255, "[2]: Russian", 1);
		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, (mDisplayY / 2) + 100, mpSystemFont, 255, 255, 255, "[3]: TBD", 1);




		mpGameSystem->getDisplay()->flipDispaly();
		break;
	case 4:

		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);

		mpGameSystem->getDisplay()->writeText(mDisplayX / 2, mDisplayY / 2, mpSystemFont, 255, 255, 255, "Game", 1);

		mpGameSystem->getDisplay()->flipDispaly();
		break;

	default:
		break;
	}

	
	
}

