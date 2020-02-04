#include "Game.h"
#include "Unit.h"
#include "System.h"
#include "GraphicsBuffer.h"
#include "Animation.h"
#include "GBufferManager.h"
#include "UnitManager.h"
//Deanlib
#include "Timer.h"
#include "PerformanceTracker.h"
//Events
#include "Event.h" 
#include "GameEvent.h"
#include "CreateUnit.h"
#include "DeleteUnit.h"
#include "ExitGame.h"
#include "SwitchHead.h"
#include "StopAnim.h"
#include "InputSystem.h"
#include "EventSystem.h"
//Mideterm
#include "Player.h"
#include "HUD.h"
#include "Centipede.h"
#include "Mushroom.h"
#include "FileReader.h"
#include "Projectile.h"
#include "Font.h"

Game * Game::mpGameInstance = nullptr;

const string ASSET_PATH = "..\\..\\shared\\assets\\";
const string DEANS = "dean_sprites.png";
const string SMURFS = "smurf_sprites.png";


using namespace std;

Game* gpGame = nullptr;

Game::Game(EventSystem* pEventSystem) 
	:EventListener(pEventSystem)
{
	
	pEventSystem->addListener((EventType)STOP_ANIMATION, this);
	pEventSystem->addListener((EventType)HEAD_SWITCH, this);
	pEventSystem->addListener((EventType)CREATE_UNIT, this);
	pEventSystem->addListener((EventType)DELETE_UNIT, this);
	pEventSystem->addListener((EventType)EXIT_GAME, this);



}

Game::Game(double fps, EventSystem* pEventSystem)		
	:EventListener(pEventSystem)
{
	mTargetTime = fps;
	pEventSystem->addListener((EventType)STOP_ANIMATION, this);
	pEventSystem->addListener((EventType)CREATE_UNIT, this);
	pEventSystem->addListener((EventType)DELETE_UNIT, this);
	pEventSystem->addListener((EventType)EXIT_GAME, this);
}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == STOP_ANIMATION) 
	{	
		if (mState == 1)
		{
			mState = 2;
		}
		else if (mState == 2)
		{
			mpUnitManager->createNewBullet(mpBulletSprite, mpPlayer->getXloc(), mpPlayer->getYloc()); //On press, create a new bullet object and add it to the vector
		}
		else if (mState == 3)
		{
			mpUnitManager->clearAllUnits();
			for (int i = 0; i < FileReader::getInstance()->getMushroomCount(); i++)
			{
				mpUnitManager->createNewMushroom(mMushroomSprites, rand() % 800, rand() % 550);
			}
			mState = 1;
		}
		
		
	}
	else if (theEvent.getType() == EXIT_GAME)
	{
		//Exit the game loop
		mShouldRunLoop = false;
	}
	else if (theEvent.getType() == DELETE_UNIT)
	{
		//const DeleteUnit& removeUnit = static_cast<const DeleteUnit&>(theEvent);
		////Delete unit
		//mpUnitManager->deleteUnit(removeUnit.getX(), removeUnit.getY(), 60);
		//Mushroom* target = dynamic_cast<Mushroom*>(mpUnitManager->getUnit(rand()%10));

		//target->looseHP();

		mState = 3;

	}
	else if (theEvent.getType() == CREATE_UNIT)
	{
		const CreateUnit& newUnit = static_cast<const CreateUnit&>(theEvent);
		
		if (newUnit.getY() < mDisplayY-300)
		{
			mpPlayer->setPlayerX(newUnit.getX());
			mpPlayer->setPlayerY(500);
		}
		else
		{
			mpPlayer->setPlayerX(newUnit.getX());
			mpPlayer->setPlayerY(newUnit.getY());
		}


		
	}

}

void Game::initGame(int screenX, int screenY, string filename, EventSystem* eventSystem)
{
	//Init system (including screen size + FPS)
	//Have system init GraphicsLib
	
	mDisplayX = screenX;
	mDisplayY = screenY;

	mpGameSystem = new System(mDisplayX, mDisplayY);
	mpBufferManager = new GBufferManager();
	mpUnitManager = new UnitManager();
	
	mpGameSystem->initSystem();

	mpInputSystem = new InputSystem();
	mpInputSystem->init(mpGameSystem, eventSystem);


																	//Centipede-specific code:

	mState = 1;
	srand(time(NULL));
	mpBufferManager->createNewBuffer("playerBuffer", 20, 15, 200, 100, 255);
	playerSprite = new Sprite(mpBufferManager->getBuffer("playerBuffer"), 0, 0, 10, 10);

	mpBufferManager->createNewBuffer("bulletBuffer", 5, 5, 255, 255, 255);
	mpBulletSprite = new Sprite(mpBufferManager->getBuffer("bulletBuffer"), 0, 0, 5, 5);

	mpPlayer = new Player(playerSprite);

	//mpUnitManager->addUnit(mpPlayer);

	mpFont = new Font(FileReader::getInstance()->getPath(), FileReader::getInstance()->getFont(), FileReader::getInstance()->getTextSize());
	mpSystemFont = new Font(FileReader::getInstance()->getPath(), FileReader::getInstance()->getFont(), 50);

	mpBufferManager->createNewBuffer("BG", mDisplayX, mDisplayY, 0, 0, 0);
	

	//Backgound conversion for drawing
	mpGameBackground = new Sprite(mpBufferManager->getBuffer("BG"),0, 0, mDisplayX, mDisplayY);

	mpBufferManager->createNewBuffer("Shroom1", FileReader::getInstance()->getPath(), FileReader::getInstance()->getMushroomVector()->at(0));
	mpBufferManager->createNewBuffer("Shroom2", FileReader::getInstance()->getPath(), FileReader::getInstance()->getMushroomVector()->at(1));
	mpBufferManager->createNewBuffer("Shroom3", FileReader::getInstance()->getPath(), FileReader::getInstance()->getMushroomVector()->at(2));
	mpBufferManager->createNewBuffer("Shroom4", FileReader::getInstance()->getPath(), FileReader::getInstance()->getMushroomVector()->at(3));

	Sprite HP_04 = Sprite(mpBufferManager->getBuffer("Shroom1"), 0, 0, mpBufferManager->getBuffer("Shroom1")->getHeight(), mpBufferManager->getBuffer("Shroom1")->getWidth());
	Sprite HP_03 = Sprite(mpBufferManager->getBuffer("Shroom2"), 0, 0, mpBufferManager->getBuffer("Shroom1")->getHeight(), mpBufferManager->getBuffer("Shroom1")->getWidth());
	Sprite HP_02 = Sprite(mpBufferManager->getBuffer("Shroom3"), 0, 0, mpBufferManager->getBuffer("Shroom1")->getHeight(), mpBufferManager->getBuffer("Shroom1")->getWidth());
	Sprite HP_01 = Sprite(mpBufferManager->getBuffer("Shroom4"), 0, 0, mpBufferManager->getBuffer("Shroom1")->getHeight(), mpBufferManager->getBuffer("Shroom1")->getWidth());

	mMushroomSprites.push_back(HP_04);
	mMushroomSprites.push_back(HP_03);
	mMushroomSprites.push_back(HP_02);
	mMushroomSprites.push_back(HP_01);

	mpBufferManager->createNewBuffer("CentiHead", FileReader::getInstance()->getPath(), FileReader::getInstance()->getCentipedeVector()->at(0));
	mpBufferManager->createNewBuffer("CentiBody", FileReader::getInstance()->getPath(), FileReader::getInstance()->getCentipedeVector()->at(1));

	Sprite centiHead = Sprite(mpBufferManager->getBuffer("CentiHead"), 0, 0, mpBufferManager->getBuffer("CentiHead")->getHeight(), mpBufferManager->getBuffer("CentiHead")->getWidth());
	Sprite centiBody = Sprite(mpBufferManager->getBuffer("CentiBody"), 0, 0, mpBufferManager->getBuffer("CentiBody")->getHeight(), mpBufferManager->getBuffer("CentiBody")->getWidth());;

	mCenitSprites.push_back(centiHead);
	mCenitSprites.push_back(centiBody);


	createNewCentipede(0);


	for (int i = 0; i < FileReader::getInstance()->getMushroomCount(); i++)
	{
		mpUnitManager->createNewMushroom(mMushroomSprites, rand() % 800, rand() % 550);
	}

}

void Game::cleanupGame()
{
	delete mpGameBackground;
	delete mpSystemFont;
	delete mpFont;
	delete mpPlayer;

	delete mpBulletSprite;
	delete playerSprite;
	//delete mpplayer

	delete mpInputSystem;
	//call system cleanup
	delete mpUnitManager;
	
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

			//cout << mpUnitManager->getNumUnitsOfType("Projectile") << std::endl;

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
	mpUnitManager->update(16.7);

	mpPlayer->checkLife();
}

void Game::draw()
{

	switch (mState)
	{
	case 1:

		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);
		mpGameSystem->getDisplay()->writeText(10, 10, mpFont, 255, 0, 0, "Player lives: " + to_string(mpPlayer->getNumLives()));
		mpGameSystem->getDisplay()->writeText(300, 10, mpFont, 255, 0, 0, "Score: " + to_string(Game::getInstance()->getScore()));
		//mpUnitManager->draw(mpGameSystem);

		

		mpGameSystem->getDisplay()->writeText(400, 300, mpSystemFont, 255, 255, 255, "Press Space To Play", 1);
		mpGameSystem->getDisplay()->flipDispaly();

		break;
	case 2:
		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);

		mpGameSystem->getDisplay()->writeText(10, 10, mpFont, 255, 0, 0, "Player lives: " + to_string(mpPlayer->getNumLives()));
		mpGameSystem->getDisplay()->writeText(300, 10, mpFont, 255, 0, 0, "Score: " + to_string(Game::getInstance()->getScore()));
		mpGameSystem->getDisplay()->writeText(600, 10, mpFont, 255, 0, 0, "FPS: " + to_string(mFPSCount));

		mpUnitManager->draw(mpGameSystem);

		mpPlayer->drawUnit(mpGameSystem);

		mpGameSystem->getDisplay()->flipDispaly();
		break;
	case 3:
		mpGameSystem->getDisplay()->draw(0, 0, mpGameBackground, 1);

		mpGameSystem->getDisplay()->writeText(10, 10, mpFont, 255, 0, 0, "Player lives: " + to_string(mpPlayer->getNumLives()));
		mpGameSystem->getDisplay()->writeText(300, 10, mpSystemFont, 255, 0, 0, "Score: " + to_string(Game::getInstance()->getScore()));

		mpUnitManager->draw(mpGameSystem);

		mpGameSystem->getDisplay()->writeText(400, 100, mpSystemFont, 255, 255, 255, "YOU DIED!", 1);
		mpGameSystem->getDisplay()->writeText(400, 300, mpSystemFont, 255, 255, 255, "Press Space To Play Again", 1);

		mpGameSystem->getDisplay()->flipDispaly();
		break;
	default:
		break;
	}

	
	
}

void Game::createNewCentipede(int increaseValue)
{
	for (int i = 0; i < 8; i++)
	{
		mpUnitManager->createNewCentipedePart(&(mCenitSprites.at(1)), (400 + 10 + i * 10), 0, FileReader::getInstance()->getCentipedeSpeed() + increaseValue);
	}

	mpUnitManager->createNewCentipedePart(&(mCenitSprites.at(0)), 400, 0, FileReader::getInstance()->getCentipedeSpeed() + increaseValue);
}