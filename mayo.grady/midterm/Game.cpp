/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Game.h"

Game * Game::mpGameInstance = nullptr;

Game::Game(EventSystem* pEventSystem)
	:EventListener(pEventSystem)
{
	mpSystem = new System();
	mpEventSystem = pEventSystem;
}

Game::~Game()
{
	cleanup();
}

void Game::init()
{
	mIsInitted = true;
	//Create performance tracker
	mpTracker = new PerformanceTracker();

	//set up level manager
	mpLevelManager = new LevelManager();

	//create level
	mpLevelManager->init(NUM_LEVELS);

	//Init system
	mpSystem->init(mpLevelManager->getLevel(mActiveLevel)->getDispWidth(), mpLevelManager->getLevel(mActiveLevel)->getDispHeight());
	mpTranslator = new InputTranslator(EventSystem::getInstance());
	mpTranslator->init();

	//set up managers
	mpGBManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
	mpWallManager = new UnitManager();
	mpFoodManager = new UnitManager();
	mpPowerUpManager = new UnitManager();

	//Create buffers
	mpGBManager->add(HEAD_KEY, mpLevelManager->getLevel(mActiveLevel)->getHeadFilename());
	mpGBManager->add(BODY_KEY, mpLevelManager->getLevel(mActiveLevel)->getBodyFilename());
	mpGBManager->add(WALL_KEY, mpLevelManager->getLevel(mActiveLevel)->getWallFilename());
	mpGBManager->add(BACKGROUND_KEY, mpLevelManager->getLevel(mActiveLevel)->getBackgroundFilename());
	mpGBManager->add(FOOD_KEY, mpLevelManager->getLevel(mActiveLevel)->getFoodFilename());
	mpGBManager->add(BONUS_KEY, mpLevelManager->getLevel(mActiveLevel)->getBonusFilename());
	mpGBManager->add(FAST_KEY, mpLevelManager->getLevel(mActiveLevel)->getFastFilename());
	mpGBManager->add(SLOW_KEY, mpLevelManager->getLevel(mActiveLevel)->getSlowFilename());
	mpGBManager->add(HUD_KEY, mpLevelManager->getLevel(mActiveLevel)->getDispWidth(), mpLevelManager->getLevel(mActiveLevel)->getDispHeight());

	//Create Animations, turning "off" animations that are only one sprite
	mpBodyAnimation = new Animation();
	mpBodyAnimation->toggleAnim();
	mpHeadAnimation = new Animation();
	mpHeadAnimation->toggleAnim();
	mpWallAnimation = new Animation();
	mpWallAnimation->toggleAnim();
	mpFoodAnimation = new Animation();
	//mpFoodAnimation->toggleAnim();
	mpBonusAnimation = new Animation();
	//mpBonusAnimation->toggleAnim();
	mpFastAnimation = new Animation();
	//mpFastAnimation->toggleAnim();
	mpSlowAnimation = new Animation();
	//mpSlowAnimation->toggleAnim();

	//Add sprites to animations
	mpBodyAnimation->addSprite(mpGBManager->getBuffer(BODY_KEY), 1, 1);
	mpHeadAnimation->addSprite(mpGBManager->getBuffer(HEAD_KEY), 1, 1);
	mpWallAnimation->addSprite(mpGBManager->getBuffer(WALL_KEY), 1, 1);
	mpFoodAnimation->addSprite(mpGBManager->getBuffer(FOOD_KEY), mpLevelManager->getLevel(mActiveLevel)->getFoodRow(), mpLevelManager->getLevel(mActiveLevel)->getFoodCol());
	mpBonusAnimation->addSprite(mpGBManager->getBuffer(BONUS_KEY), mpLevelManager->getLevel(mActiveLevel)->getBonusRow(), mpLevelManager->getLevel(mActiveLevel)->getBonusCol());
	mpFastAnimation->addSprite(mpGBManager->getBuffer(FAST_KEY), mpLevelManager->getLevel(mActiveLevel)->getFastRow(), mpLevelManager->getLevel(mActiveLevel)->getFastCol());
	mpSlowAnimation->addSprite(mpGBManager->getBuffer(SLOW_KEY), mpLevelManager->getLevel(mActiveLevel)->getSlowRow(), mpLevelManager->getLevel(mActiveLevel)->getSlowCol());

	//prep font
	textFont = new Font(mpLevelManager->getLevel(mActiveLevel)->getFontSize(), mpLevelManager->getLevel(mActiveLevel)->getAssetPath() + mpLevelManager->getLevel(mActiveLevel)->getFontFilename());
	//cout << mpLevelManager->getLevel(mActiveLevel)->getFontFilename();

	//initialize speed value
	setSpeed();

	//create snake
	createSnake();

	//create walls
	spawnWalls();

	//spawn first food
	spawnFood();

	spawnPowerUp();

	//set the target number of segment for level 1
	mTargetSegments = mpLevelManager->getLevel(mActiveLevel)->getTarget();

	//Add Event Listeners
	mpEventSystem->addListener((EventType)EXIT_GAME_EVENT, this);
	mpEventSystem->addListener((EventType)ADD_UNIT_EVENT, this);
	mpEventSystem->addListener((EventType)REMOVE_UNIT_EVENT, this);
	mpEventSystem->addListener((EventType)SWAP_ANIMATION_EVENT, this);
	mpEventSystem->addListener((EventType)TOGGLE_ANIMATION_EVENT, this);
	mpEventSystem->addListener((EventType)TURN_UP_EVENT, this);
	mpEventSystem->addListener((EventType)TURN_DOWN_EVENT, this);
	mpEventSystem->addListener((EventType)TURN_LEFT_EVENT, this);
	mpEventSystem->addListener((EventType)TURN_RIGHT_EVENT, this);
	mpEventSystem->addListener((EventType)START_GAME_EVENT, this);
}

void Game::cleanup()
{
	if (mIsInitted)
	{
		mIsInitted = false;
		
		delete textFont;
		delete mpSlowAnimation;
		delete mpFastAnimation;
		delete mpBonusAnimation;
		delete mpFoodAnimation;
		delete mpWallAnimation;
		delete mpHeadAnimation;
		delete mpBodyAnimation;
		mpPowerUpManager->cleanup();
		delete mpPowerUpManager;
		mpFoodManager->cleanup();
		delete mpFoodManager;
		mpWallManager->cleanup();
		delete mpWallManager;
		mpUnitManager->cleanup();
		delete mpUnitManager;
		mpGBManager->cleanup();
		delete mpGBManager;
		delete mpTranslator;
		mpLevelManager->cleanup();
		delete mpLevelManager;
		delete mpTracker;
		delete mpSystem;
	}
}

void Game::doLoop()
{
	while (mKeepGoing)
	{
		mpSystem->getInputSystem()->update();
		//performance tracker -> start
		mpTracker->clearTracker(TRACKER);
		mpTracker->startTracking(TRACKER);

		mTheTimer.start();
		if (mStartGame == false)
		{
			if (mWin)
			{
				drawWin();
			}
			else if (mLoss)
			{
				drawLoss();
			}
			else
			{
				drawStart();
			}
		}
		if (mStartGame == true)
		{
			//loop processing
			//draw statements
			render();

			//update to next animation frame
			mpUnitManager->update(mpLevelManager->getLevel(mActiveLevel)->getDesiredFPS());
			mpWallManager->update(mpLevelManager->getLevel(mActiveLevel)->getDesiredFPS());
			mpFoodManager->update(mpLevelManager->getLevel(mActiveLevel)->getDesiredFPS());
			mpPowerUpManager->update(mpLevelManager->getLevel(mActiveLevel)->getDesiredFPS());

			//move the snake based on speed
			int powerUpInterval = mpLevelManager->getLevel(mActiveLevel)->getPowerFreq();

			if (mSpeedCounter == mSpeed)
			{
				moveSnake();
				mSpeedCounter = 0;
				//cout << mScore << endl;
				//cout << mSpeed << endl;
			}
			mSpeedCounter++;
			if (mPowerUpCounter == powerUpInterval)
			{
				spawnPowerUp();
				mPowerUpCounter = 0;
			}
			mPowerUpCounter++;
		}
		mTheTimer.sleepUntilElapsed(mpLevelManager->getLevel(mActiveLevel)->getDesiredFPS());

		//performance tracker -> stop
		mpTracker->stopTracking(TRACKER);
		//cout << mpTracker->getElapsedTime(TRACKER) << endl;

		mFPS = mpTracker->getElapsedTime(TRACKER);
	}
}

void Game::render()
{
	//(re)draw background
	mpSystem->getGraphicsSystem()->draw(mpGBManager->getBuffer(BACKGROUND_KEY), ZERO, ZERO, BASE_SCALE);
	
	//draw unit then update to next animation frame
	mpUnitManager->draw();
	mpWallManager->draw();
	mpFoodManager->draw();
	mpPowerUpManager->draw();

	drawHUD(mFPS);

	//flip diaplay
	mpSystem->getGraphicsSystem()->flip();
}

void Game::spawnWalls()
{
	//spawn borders
	int squaresInRow = mpLevelManager->getLevel(mActiveLevel)->getDispWidth() / mpLevelManager->getLevel(mActiveLevel)->getSpriteSize();
	for (int i = 0; i < squaresInRow; i++)
	{
		mpWallManager->add(Vector2D((i * mpLevelManager->getLevel(mActiveLevel)->getSpriteSize()), ZERO));
		mpWallManager->getUnit(mpWallManager->getCollectionSize() - 1)->setAnimation(mpWallAnimation);
		mpWallManager->add(Vector2D((i * mpLevelManager->getLevel(mActiveLevel)->getSpriteSize()), mpLevelManager->getLevel(mActiveLevel)->getDispWidth() - mpLevelManager->getLevel(mActiveLevel)->getSpriteSize()));
		mpWallManager->getUnit(mpWallManager->getCollectionSize() - 1)->setAnimation(mpWallAnimation);
	}
	int squaresInColumn = squaresInRow - 1;
	for (int i = 1; i < squaresInColumn; i++)
	{
		mpWallManager->add(Vector2D(ZERO, (i * mpLevelManager->getLevel(mActiveLevel)->getSpriteSize())));
		mpWallManager->getUnit(mpWallManager->getCollectionSize() - 1)->setAnimation(mpWallAnimation);
		mpWallManager->add(Vector2D(mpLevelManager->getLevel(mActiveLevel)->getDispHeight() - mpLevelManager->getLevel(mActiveLevel)->getSpriteSize(), (i * mpLevelManager->getLevel(mActiveLevel)->getSpriteSize())));
		mpWallManager->getUnit(mpWallManager->getCollectionSize() - 1)->setAnimation(mpWallAnimation);
	}

	//spawn interior walls
	int numW = mpLevelManager->getLevel(mActiveLevel)->getNumWalls();
	for (int i = 0; i < numW; i++)
	{
		mpWallManager->add(Vector2D(mpLevelManager->getLevel(mActiveLevel)->getWPos(i)->getX(), mpLevelManager->getLevel(mActiveLevel)->getWPos(i)->getY()));
		mpWallManager->getUnit(mpWallManager->getCollectionSize() - 1)->setAnimation(mpWallAnimation);
	}
}

void Game::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == EXIT_GAME_EVENT)
	{
		mKeepGoing = false;
	}
	if (theEvent.getType() == START_GAME_EVENT)
	{
		//cout << "start game" << endl;
		mStartGame = true;
		if (mGameEnded)
		{
			//resetGame
			mActiveLevel = 1;
			mScore = 0;

			//cleanup sprites
			mpPowerUpManager->cleanup();
			mpFoodManager->cleanup();
			mpWallManager->cleanup();
			mpUnitManager->cleanup();

			//reset direction of travel to the right
			mDirection = "right";

			//reset speed
			setSpeed();

			//create new sprites
			createSnake();
			spawnWalls();
			spawnFood();
		}
	}
	if (theEvent.getType() == TURN_UP_EVENT)
	{
		//cout << "UP" << endl;
		mDirection = "up";
	}
	if (theEvent.getType() == TURN_DOWN_EVENT)
	{
		mDirection = "down";
	}
	if (theEvent.getType() == TURN_LEFT_EVENT)
	{
		mDirection = "left";
	}
	if (theEvent.getType() == TURN_RIGHT_EVENT)
	{
		mDirection = "right";
	}
}

void Game::moveSnake()
{
	Unit * pHead = mpUnitManager->getUnit(0);
	mNextLoc = pHead->getLocation();
	
	//cout << mDirection << endl;
	if (mDirection == "right")
	{
		mNewLoc = Vector2D(pHead->getLocation().getX() + mpLevelManager->getLevel(mActiveLevel)->getSpriteSize(), pHead->getLocation().getY());
		pHead->setLocation(mNewLoc.getX(), mNewLoc.getY());
	}
	if (mDirection == "left")
	{
		mNewLoc = Vector2D(pHead->getLocation().getX() - mpLevelManager->getLevel(mActiveLevel)->getSpriteSize(), pHead->getLocation().getY());
		pHead->setLocation(mNewLoc.getX(), mNewLoc.getY());
	}
	if (mDirection == "up")
	{
		mNewLoc = Vector2D(pHead->getLocation().getX(), pHead->getLocation().getY() - mpLevelManager->getLevel(mActiveLevel)->getSpriteSize());
		pHead->setLocation(mNewLoc.getX(), mNewLoc.getY());
	}
	if (mDirection == "down")
	{
		mNewLoc = Vector2D(pHead->getLocation().getX(), pHead->getLocation().getY() + mpLevelManager->getLevel(mActiveLevel)->getSpriteSize());
		pHead->setLocation(mNewLoc.getX(), mNewLoc.getY());
	}

	//check for collision
	checkForCollision(mNewLoc);

	//iterate through snake moving to the previous piece's location
	for (int i = 1; i < mpUnitManager->getCollectionSize(); i++)
	{
		mPreviousLoc = mpUnitManager->getUnit(i)->getLocation();
		mpUnitManager->getUnit(i)->setLocation(mNextLoc.getX(), mNextLoc.getY());
		mNextLoc = mPreviousLoc;
	}
}

void Game::checkForCollision(Vector2D target)
{
	//loop through wall list to check for a collision
	for (int i = 0; i < mpWallManager->getCollectionSize(); i++)
	{
		if (mpWallManager->getUnit(i)->getLocation() == target)
		{
			//crash detected
			//cout << "crash detected" << endl;
			//Game Over
			mStartGame = false;
			mLoss = true;
		}
	}

	//loop through segement list to check for collision
	for (int i = 1; i < mpUnitManager->getCollectionSize(); i++)
	{
		if (mpUnitManager->getUnit(i)->getLocation() == target)
		{
			//crash detected
			//cout << "crash detected" << endl;
			//Game Over
			mStartGame = false;
			mLoss = true;
		}
	}

	//loop through food list to check for collision
	for (int i = 0; i < mpFoodManager->getCollectionSize(); i++)
	{
		if (mpFoodManager->getUnit(i)->getLocation() == target)
		{
			//cout << "eat food" << endl;
			//grow snake
			addSegment();

			//move food to a new location
			Vector2D newLocation = randomLocation();
			mpFoodManager->getUnit(i)->setLocation(newLocation.getX(), newLocation.getY());

			//increase score
			mScore += mpLevelManager->getLevel(mActiveLevel)->getFoodScore();
			
			checkWin();
		}
	}

	//loop through power-up list to check for collision
	for (int i = 0; i < mpPowerUpManager->getCollectionSize(); i++)
	{
		if (mpPowerUpManager->getUnit(i)->getLocation() == target)
		{
			//apply power-up
			//cout << "collected" << endl;
			applyPowerUp(mpPowerUpManager->getUnit(i)->getID());

			//clear the power up after collection
			mpPowerUpManager->remove(i);
		}
	}
}

//spawn a snake starting with a head, the a body based on the number of segements 
void Game::createSnake()
{
	mpUnitManager->add(Vector2D(CENTER_X, CENTER_Y));
	mpUnitManager->getUnit(mpUnitManager->getCollectionSize() - 1)->setAnimation(mpHeadAnimation);
	int segments = mpLevelManager->getLevel(mActiveLevel)->getSegments();
	for (int i = 0; i < segments; i++)
	{
		int offset = CENTER_X - (mpLevelManager->getLevel(mActiveLevel)->getSpriteSize() * i);
		mpUnitManager->add(Vector2D(offset, CENTER_Y));
		mpUnitManager->getUnit(mpUnitManager->getCollectionSize() - 1)->setAnimation(mpBodyAnimation);
	}
}

//add a segement to the end of the snake
void Game::addSegment()
{
	mpUnitManager->add(mPreviousLoc);
	mpUnitManager->getUnit(mpUnitManager->getCollectionSize() - 1)->setAnimation(mpBodyAnimation);
}

//spawn foor in a random location
void Game::spawnFood()
{
	mpFoodManager->add(randomLocation());
	mpFoodManager->getUnit(mpFoodManager->getCollectionSize() - 1)->setAnimation(mpFoodAnimation);
}

bool Game::checkSpawn(Vector2D target)
{
	//loop through wall list to check for a collision
	for (int i = 0; i < mpWallManager->getCollectionSize(); i++)
	{
		if (mpWallManager->getUnit(i)->getLocation() == target)
		{
			return false;
		}
	}
	//loop through segement list to check for collision
	for (int i = 1; i < mpUnitManager->getCollectionSize(); i++)
	{
		if (mpUnitManager->getUnit(i)->getLocation() == target)
		{
			return false;
		}
	}
	return true;
}

Vector2D Game::randomLocation()
{
	int randomX = 0;
	int randomY = 0;
	Vector2D targetLoc;
	do
	{
		int upperLimitX = mpLevelManager->getLevel(mActiveLevel)->getDispWidth() / mpLevelManager->getLevel(mActiveLevel)->getSpriteSize();
		int upperLimitY = mpLevelManager->getLevel(mActiveLevel)->getDispHeight() / mpLevelManager->getLevel(mActiveLevel)->getSpriteSize();
		srand(time(NULL));
		randomX = 1 + rand() % (upperLimitX - 1);
		randomY = 1 + rand() % (upperLimitY - 1);
		targetLoc.setX(randomX *  mpLevelManager->getLevel(mActiveLevel)->getSpriteSize());
		targetLoc.setY(randomY *  mpLevelManager->getLevel(mActiveLevel)->getSpriteSize());
	} while (checkSpawn(targetLoc) == false);
	//cout << targetLoc.getX() << " , " << targetLoc.getY() << endl;
	return targetLoc;
}

void Game::checkWin()
{
	if (mTargetSegments == mpUnitManager->getCollectionSize())
	{
		if (mActiveLevel == NUM_LEVELS)
		{
			//draw congratulations
			//cout << "you win" << endl;
			mStartGame = false;
			mWin = true;
		}
		else
		{
			//load new level
			mActiveLevel++;
			//cout << "new Level" << mActiveLevel << endl;
			
			//cleanup sprites
			mpPowerUpManager->cleanup();
			mpFoodManager->cleanup();
			mpWallManager->cleanup();
			mpUnitManager->cleanup();

			//reset direction of travel to the right
			mDirection = "right";

			//reset speed
			setSpeed();

			//create new sprites
			createSnake();
			spawnWalls();
			spawnFood();
		}
	}
}

void Game::spawnPowerUp()
{
	//cout << "power-up" << endl;
	srand(time(NULL) + 300);
	int powerUpNum = rand() % 3;
	if (powerUpNum == 0)
	{
		//spawn bonus
		//cout << "bonus" << endl;
		mpPowerUpManager->add(randomLocation());
		mpPowerUpManager->getUnit(mpPowerUpManager->getCollectionSize() - 1)->setAnimation(mpBonusAnimation);
		mpPowerUpManager->getUnit(mpPowerUpManager->getCollectionSize() - 1)->setID(0);
	}
	if (powerUpNum == 1)
	{
		//spawn fast
		//cout << "fast" << endl;
		mpPowerUpManager->add(randomLocation());
		mpPowerUpManager->getUnit(mpPowerUpManager->getCollectionSize() - 1)->setAnimation(mpFastAnimation);
		mpPowerUpManager->getUnit(mpPowerUpManager->getCollectionSize() - 1)->setID(1);
	}
	if (powerUpNum == 2)
	{
		//spawn slow
		//cout << "slow" << endl;
		mpPowerUpManager->add(randomLocation());
		mpPowerUpManager->getUnit(mpPowerUpManager->getCollectionSize() - 1)->setAnimation(mpSlowAnimation);
		mpPowerUpManager->getUnit(mpPowerUpManager->getCollectionSize() - 1)->setID(2);
	}
	//cout << mpPowerUpManager->getCollectionSize() << endl;
}

void Game::applyPowerUp(int type)
{
	if (type == 0)
	{
		//cout << "add score" << endl;
		mScore += mpLevelManager->getLevel(mActiveLevel)->getBonusValue();
	}
	if (type == 1)
	{
		//cout << "speed up" << endl;
		mSpeed -= mpLevelManager->getLevel(mActiveLevel)->getFastValue();
		if(mSpeed < 5)
		{
			mSpeed = 5;
		}
	}
	if (type == 2)
	{
		//cout << "slow down" << endl;
		mSpeed += mpLevelManager->getLevel(mActiveLevel)->getSlowValue();
	}
}

void Game::setSpeed()
{
	mSpeed = mpLevelManager->getLevel(mActiveLevel)->getSpeed();
}

void Game::drawHUD(double time)
{
	//cout << "draw hud" << endl;
	stringstream levelStream;
	stringstream scoreStream;
	stringstream fpsStream;
	levelStream << "Level " << mActiveLevel;
	scoreStream << "Score: " << mScore;
	fpsStream << "FPS: " << MILLI_SEC / time;
	Color yellowColor(255, 255, 0);
	Color blackColor(0, 0, 0);
	mpSystem->getGraphicsSystem()->writeText(0, 0, textFont, yellowColor, levelStream.str());
	mpSystem->getGraphicsSystem()->writeText(200, 0, textFont, yellowColor, scoreStream.str());
	mpSystem->getGraphicsSystem()->writeText(400, 0, textFont, yellowColor, fpsStream.str());
}

void Game::drawLoss()
{
	mGameEnded = true;
	//cout << "loss" << endl;
	stringstream lossStream;
	lossStream << "Your score was: " << mScore;
	Color blueColor(0, 0, 255);
	mpSystem->getGraphicsSystem()->draw(mpGBManager->getBuffer(BACKGROUND_KEY), ZERO, ZERO, BASE_SCALE);
	mpSystem->getGraphicsSystem()->writeText(225, CENTER_Y, textFont, blueColor, "GAME OVER");
	mpSystem->getGraphicsSystem()->writeText(145, CENTER_Y + 30, textFont, blueColor, lossStream.str());
	mpSystem->getGraphicsSystem()->writeText(100, CENTER_Y + 60, textFont, blueColor, "Press SPACE to Play Again");
	mpSystem->getGraphicsSystem()->flip();
}

void Game::drawWin()
{
	mGameEnded = true;
	//cout << "win" << endl;
	stringstream winStream;
	winStream << "Your score was: " << mScore;
	Color blueColor(0, 0, 255);
	mpSystem->getGraphicsSystem()->draw(mpGBManager->getBuffer(BACKGROUND_KEY), ZERO, ZERO, BASE_SCALE);
	mpSystem->getGraphicsSystem()->writeText(225, CENTER_Y, textFont, blueColor, "YOU WIN!");
	mpSystem->getGraphicsSystem()->writeText(145, CENTER_Y + 30, textFont, blueColor, winStream.str());
	mpSystem->getGraphicsSystem()->writeText(100, CENTER_Y + 60, textFont, blueColor, "Press SPACE to Play Again");
	mpSystem->getGraphicsSystem()->flip();
}

void Game::drawStart()
{
	Color blueColor(0, 0, 255);
	mpSystem->getGraphicsSystem()->draw(mpGBManager->getBuffer(BACKGROUND_KEY), ZERO, ZERO, BASE_SCALE);
	mpSystem->getGraphicsSystem()->writeText(160, CENTER_Y, textFont, blueColor, "Welcome to SNAKE");
	mpSystem->getGraphicsSystem()->writeText(125, CENTER_Y + 30, textFont, blueColor, "Press SPACE to Start");
	mpSystem->getGraphicsSystem()->flip();
}