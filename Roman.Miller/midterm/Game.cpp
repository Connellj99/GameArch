#include "Event.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include "EventSystem.h"
#include "GameEvent.h"
#include <fstream>
#include <sstream>

Game* Game::mpsGameInstance = nullptr;

void Game::render()
{
	mSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpBackgroundSprite, 1);

	if (isPlaying ==1)
	{
		mUnitManager.draw();
		mOnScreenText->Print(mLevelManager.getLevel(), mLevelManager.getCurrentPoints(), getCurrentFPS());
		mSnakeManager.draw();
	}
	else if( isPlaying ==0)
	{
		mOnScreenText->Print("Press Space to Start");
	}
	else if (isPlaying == 2)
	{
		mOnScreenText->Print("YOU WIN");
	}
	else if (isPlaying == 3)
	{
		mOnScreenText->Print("YOU LOSE");
	}

	mSystem->getGraphicsSystem()->flip();
}

void Game::update()
{
	checkForItemSpawn();
	mpInputSystem->update();
	mUnitManager.updateUnit();
	if (isPlaying == 1)
	{
		mSnakeManager.update(mCurrentMiliPerFrame);
	}
	
}




Game::Game()
	:EventListener(EventSystem::getInstance())
{
	//Declare any pointers null
}

Game::~Game()
{
	cleanup();
}

void Game::readGameFile()
{
	fstream fin;
	fin.open("Values.txt");

	getline(fin, FOOD_FILENAME);
	getline(fin, SLOW_FILENAME);
	getline(fin, SPEED_FILENAME);
	getline(fin, SNAKE_FILENAME);
	getline(fin, BACKGROUND_FILENAME);
	getline(fin, TEXT_FILENAME);
	getline(fin, ASSET_PATH);


	string tempOne, tempTwo, tempThree, sFood;
	int one, two, three, food;

	getline(fin, sFood);
	getline(fin, tempOne);
	getline(fin, tempTwo);
	getline(fin, tempThree);

	one = stoi(tempOne);
	two = stoi(tempTwo);
	three = stoi(tempThree);
	food = stoi(sFood);

	mLevelManager.setLevelPointValues(one, two, three, food);

	string temp;
	getline(fin, temp);

	mPowerInterval = stof(temp);

	getline(fin, temp);
	mStartingSegs = stoi(temp);
}

void Game::initInstance()
{
	//as long as no other deal is there make one
	if (mpsGameInstance == nullptr)
	{
		mpsGameInstance = new Game();

	}
	else
	{
		assert(mpsGameInstance != nullptr);
	}
	
}

void Game::cleanupInstance()
{
	delete mpsGameInstance;
	mpsGameInstance = nullptr;
}

void Game::doLoop()
{
	PerformanceTracker tracker = PerformanceTracker();
	mFoodTimer.start();
	mPowerTimer.start();
	while (mLoopGame)
	{
		tracker.clearTracker(TRACKER);
		tracker.startTracking(TRACKER);
		mTimer.start();
		//--
		update();
		render();
		mTimer.sleepUntilElapsed(mframeTime);
		//--
		tracker.stopTracking(TRACKER);
		mCurrentMiliPerFrame = tracker.getElapsedTime(TRACKER);
		cout << tracker.getElapsedTime(TRACKER) << endl;
	}
	mFoodTimer.stop();
	mPowerTimer.stop();
}

Game * Game::getInstance()
{
	assert(mpsGameInstance);
	return mpsGameInstance;
}

void Game::init(Vector2D screenSize, float targetFrameRate)
{
	isPlaying = 0;

	mpInputSystem = new InputSystem();
	mpInputTranslator = new InputTranslator(EventSystem::getInstance());
	mSystem = new System();
	mSystem->init();
	mBufferManager = GraphicsBufferManager();
	mUnitManager = UnitManager();
	mLevelManager = LevelManager();
	mSnakeManager = SnakeManager();

	readGameFile();

	

	//Set screen and frame variables
	mScreenSize = screenSize;
	mframeTime = 1000 / targetFrameRate;

	//Set up HUD
	mTextColor = Color(191, 62, 292, 1);
	mOnScreenText = new OnScreenText();
	mOnScreenText->Init(new Font(ASSET_PATH, TEXT_FILENAME, 40), mTextColor);

	//create buffers and add to manager
	mBufferManager.addBuffer(FOOD_KEY  ,new GraphicsBuffer(ASSET_PATH + FOOD_FILENAME));
	mBufferManager.addBuffer(SNAKE_KEY, new GraphicsBuffer(ASSET_PATH + SNAKE_FILENAME));
	mBufferManager.addBuffer(SPEED_KEY, new GraphicsBuffer(ASSET_PATH + SPEED_FILENAME));
	mBufferManager.addBuffer(SLOW_KEY, new GraphicsBuffer(ASSET_PATH + SLOW_FILENAME));

	mBufferManager.addBuffer(BACKGROUND_KEY, new GraphicsBuffer(ASSET_PATH + BACKGROUND_FILENAME));
	mpBackgroundSprite = new Sprite(mBufferManager.getBuffer(BACKGROUND_KEY), Vector2D(0, 0),Vector2D( mBufferManager.getBuffer(BACKGROUND_KEY)->getWidth(), mBufferManager.getBuffer(BACKGROUND_KEY)->getHeight()));

	//Set up Snake
	Animation tempUnit = Animation(*mBufferManager.getBuffer(SNAKE_KEY), Vector2D(50, 50));
	mSnakeManager.init(Unit(tempUnit, Vector2D(400, 400), SNAKE_KEY),mStartingSegs);

	EventSystem::getInstance()->addListener((EventType)EXIT_GAME, this);
	EventSystem::getInstance()->addListener((EventType)START, this);

	EventSystem::getInstance()->addListener((EventType)UP, this);
	EventSystem::getInstance()->addListener((EventType)DOWN, this);
	EventSystem::getInstance()->addListener((EventType)LEFT, this);
	EventSystem::getInstance()->addListener((EventType)RIGHT, this);

	EventSystem::getInstance()->addListener((EventType)DESTROY_FOOD, this);
	EventSystem::getInstance()->addListener((EventType)CREATE_FOOD, this);
	EventSystem::getInstance()->addListener((EventType)DRESTROY_POWERUP, this);
	EventSystem::getInstance()->addListener((EventType)CREATE_POWERUP, this);

	EventSystem::getInstance()->addListener((EventType)EAT, this);
	EventSystem::getInstance()->addListener((EventType)SLOW, this);
	EventSystem::getInstance()->addListener((EventType)SPEED, this);
}

void Game::cleanup()
{
	mOnScreenText->CleanUp();
	delete mOnScreenText;
	mOnScreenText = nullptr;
	delete mpBackgroundSprite;
	mpBackgroundSprite = nullptr;
	mSystem->cleanup();
	delete mSystem;
	mSystem = nullptr;
	delete mpInputTranslator;
	mpInputTranslator = nullptr;
	delete mpInputSystem;
	mpInputSystem = nullptr;
}

void Game::checkCollision(Vector2D pos)
{
	mUnitManager.checkOverlap(pos);
}

System* Game::getSystem()
{
	return mSystem;
}

void Game::handleEvent(const Event & theEvent)
{
	if (theEvent.getType() == EXIT_GAME)
	{
		exitDoloop();
	}
	else if (theEvent.getType() == START)
	{
		isPlaying = true;
	}
	else if (theEvent.getType() == CREATE_FOOD)
	{
		spawnFood();
	}
	else if (theEvent.getType() == CREATE_POWERUP)
	{
		spawnPower();
	}
	else if (theEvent.getType() == DESTROY_FOOD)
	{

	}
	else if (theEvent.getType() == DRESTROY_POWERUP)
	{

	}
	else if (theEvent.getType() == UP)
	{
		mSnakeManager.setDirection(0);
	}
	else if (theEvent.getType() == DOWN)
	{
		mSnakeManager.setDirection(2);
	}
	else if (theEvent.getType() == LEFT)
	{
		mSnakeManager.setDirection(3);
	}
	else if (theEvent.getType() == RIGHT)
	{
		mSnakeManager.setDirection(1);
	}
	else if (theEvent.getType() == EAT)
	{
		if (mLevelManager.getLevel() == 1)
		{
			mSnakeManager.addSegment();
		}
		else if (mLevelManager.getLevel() == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				mSnakeManager.addSegment();
			}
		}
		else if (mLevelManager.getLevel() == 3)
		{
			for (int i = 0; i < 5; i++)
			{
				mSnakeManager.addSegment();
			}
		}
		
		mLevelManager.foodColleted();
	}
	else if (theEvent.getType() == SPEED)
	{
		mSnakeManager.speedUp();
	}
	else if (theEvent.getType() == SLOW)
	{
		mSnakeManager.slowDown();
	}
}

void Game::createNewUnit(Vector2D loc)
{
	vector<Animation> temp;
}

void Game::deleteUnitAtLoc(Vector2D loc)
{
	mUnitManager.deleteByPosition(loc);
}

void Game::exitDoloop()
{
	mLoopGame = false;
}

void Game::checkForItemSpawn()
{

	if (!mUnitManager.containsObjectOfType(FOOD_KEY))
	{
		EventSystem::getInstance()->fireEvent((EventType)CREATE_FOOD);
	}
	if (mPowerTimer.getElapsedTime() >= mPowerInterval)
	{
		mPowerTimer.start();
		spawnPower();
	}
}

void Game::spawnFood()
{
	Vector2D loc =Vector2D( rand() % 16, rand() % 16);
	loc = Vector2D(loc.getX() * 50, loc.getY() * 50);
	mUnitManager.createUnit(Animation(*mBufferManager.getBuffer(FOOD_KEY), Vector2D(50, 50)), loc,FOOD_KEY);
}

void Game::spawnPower()
{
	Vector2D loc = Vector2D(rand() % 16, rand() % 16);
	loc = Vector2D(loc.getX() * 50, loc.getY()*50);
	int num = rand() % 2;
	if (num == 0)
	{
		mUnitManager.createUnit(Animation(*mBufferManager.getBuffer(SPEED_KEY), Vector2D(50, 50)), loc, SPEED_KEY);
	}
	else if (num == 1)
	{
		mUnitManager.createUnit(Animation(*mBufferManager.getBuffer(SLOW_KEY), Vector2D(50, 50)), loc, SLOW_KEY);
	}
	
}

int Game::getCurrentFPS()
{
	int temp = 1000 / mCurrentMiliPerFrame;
	return temp;
}

