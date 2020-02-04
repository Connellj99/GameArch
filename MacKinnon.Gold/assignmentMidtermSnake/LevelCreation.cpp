#include "LevelCreation.h"
//#include "LevelOutline.h"
#include "ChangeDirectionEvent.h"

LevelCreation::LevelCreation() : LevelOutline()
{

}


LevelCreation::~LevelCreation()
{
	cleanup();
}


//initializes the level
void LevelCreation::init(System* system, string level, string fileName, int rows, int cols) 
{
	LevelOutline::init(system, level);
	mFileName = fileName;
	mCols = cols;
	mRows = rows;
	mLevel = level;

	mpSnakeUnit = new SnakeUnit();
	mpFont = new Font(ASSET_PATH + GAME_FONT, 20);
	
	mpUnitManager = new UnitManager();
	mpGraphicsBufferManager = new GraphicsBufferManager();

	mpSystem = getSystem();

	
	readDataFile(fileName);

	initSettings();

	mpSystem = getSystem();

	EventSystem::getInstance()->addListener((EventType)CHANGE_DIRECTION_EVENT, this);

	srand(time(NULL));

	//supposed to create sprite vectors for animations
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			mpWallList.push_back(new Sprite((x * 32), (y * 32), 32, 32, mpGraphicsBufferManager->getGraphicsBuffer(mWallKey)));
			mpFoodList.push_back(new Sprite((x * 32), (y * 32), 32, 32, mpGraphicsBufferManager->getGraphicsBuffer(mFoodKey)));
			mpSpeedDownList.push_back(new Sprite((x * 32), (y * 32), 32, 32, mpGraphicsBufferManager->getGraphicsBuffer(mSpeedDownKey)));
			mpSpeedUpList.push_back(new Sprite((x * 32), (y * 32), 32, 32, mpGraphicsBufferManager->getGraphicsBuffer(mSpeedUpKey)));
			mpExtraPointsList.push_back(new Sprite((x * 32), (y * 32), 32, 32, mpGraphicsBufferManager->getGraphicsBuffer(mExtraPointsKey)));
		}
	}

	mpSnakeList.push_back(new Sprite(0, 0, 32, 32, mpGraphicsBufferManager->getGraphicsBuffer(mSnakeKey)));

	mCellWidth = DISP_WIDTH / mCols;
	mCellHeight = DISP_HEIGHT / mRows;

	//create grid
	initGrid(rows, cols);

	//create walls
	for (unsigned int i = 0; i < mWallPositions.size(); i++) 
	{
		initWall(Vector2D(mWallPositions[i].getX(), mWallPositions[i].getY()));
	}
	//create snake
	for (unsigned int i = 0; i < mSnakePositions.size(); i++)
	{
		initSnake(Vector2D(mSnakePositions[i].getX(), mSnakePositions[i].getY()));
	}
	//create food spawned randomly
	//initFood(randomPositionGenerator());
	initSpeedDown(randomPositionGenerator());
	initSpeedUp(randomPositionGenerator());

}

//cleanup function
void LevelCreation::cleanup() 
{

	delete mpSnakeUnit;

	delete mpUnitManager;

	delete mpFont;

	for (unsigned int i = 0; i < mpSnakeList.size(); i++)
	{
		delete mpSnakeList[i];
	}
	for (unsigned int i = 0; i < mpWallList.size(); i++)
	{
		delete mpWallList[i];
	}
	for (unsigned int i = 0; i < mpSpeedDownList.size(); i++)
	{
		delete mpSpeedDownList[i];
	}
	for (unsigned int i = 0; i < mpSpeedUpList.size(); i++)
	{
		delete mpSpeedUpList[i];
	}
	for (unsigned int i = 0; i < mpFoodList.size(); i++)
	{
		delete mpFoodList[i];
	}
	for (unsigned int i = 0; i < mpExtraPointsList.size(); i++)
	{
		delete mpExtraPointsList[i];
	}

	EventSystem::getInstance()->removeListener((EventType)CHANGE_DIRECTION_EVENT, this);

	delete mpGraphicsBufferManager;

	LevelOutline::cleanup();
}

//resets the level if it needs to be reloaded
void LevelCreation::reset() 
{
	delete mpSnakeUnit;
	delete mpUnitManager;

	mpUnitManager = new UnitManager();
	mpSnakeUnit = new SnakeUnit();

	initGrid(mRows, mCols);

	mScore = 0;
	mFalseDeathCalls = 0;

	
	for (unsigned int i = 0; i < mWallPositions.size(); i++)
	{
		initWall(Vector2D(mWallPositions[i].getX(), mWallPositions[i].getY()));
	}

	for (unsigned int i = 0; i < mSnakePositions.size(); i++)
	{
		initSnake(Vector2D(mSnakePositions[i].getX(), mSnakePositions[i].getY()));
	}

	//EventSystem::getInstance()->fireEvent(ChangeDirectionEvent(0, 0));


	initSpeedDown(randomPositionGenerator());
	initSpeedUp(randomPositionGenerator());


	//initFood(randomPositionGenerator());

}

//updaes the level
void LevelCreation::update(double time) 
{

	mpUnitManager->update(time / 1000.0);

	mpSnakeUnit->update(time / 1000.0, mGameSpace);


	mPowerUpTimeTracker += (time / 1000.0);

	//randomly places a powerup after a set time has passed
	/*if (mPowerUpTimeTracker > mPowerUpTimer) 
	{
		placePowerUps();
		mPowerUpTimeTracker = 0;
	
	}*/

	render();
	//mpSystem->getGraphicsSystem()->writeText(150, 550, mpFont, Color(255, 255, 255), ("FPS: " + to_string(frameRate)));


	collisionCheck();
}


//renders the level
void LevelCreation::render() 
{
	mpSystem->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(mBackgroundKey), SCALE_FACTOR);

	mpUnitManager->draw();
	//mpUnitManager->draw(mpSystem, mCellWidth, mCellHeight);
	mpSnakeUnit->draw(mpSystem, mCellHeight, mCellWidth);
	drawText();

	mpSystem->getGraphicsSystem()->flipDisplay();
}


//creates the game space
void LevelCreation::initGrid(int rows, int cols)
{
	mGameSpace = vector<vector<TileTypes>>(cols);//cols
	for (int x = 0; x < mCols; x++)
	{
		mGameSpace[x] = vector<TileTypes>(rows);//rows
		for (int y = 0; y < mRows; y++)
		{
			if (x == 0 || x == mCols - 1)
			{
				mGameSpace[x][y] = TileTypes::WALL_TILE;
				mpUnitManager->addUnit(Vector2D(x * mCellWidth, y * mCellHeight), mpWallList);
			}
			else if (y == 0 || y == mRows - 1)
			{
				mGameSpace[x][y] = TileTypes::WALL_TILE;
				mpUnitManager->addUnit(Vector2D(x * mCellWidth, y * mCellHeight), mpWallList);
			}
			else
			{
				mGameSpace[x][y] = TileTypes::EMPTY_TILE;
			}
		}
	}
}

//places a wall at grid position
void LevelCreation::initWall(Vector2D loc)
{
	mGameSpace[loc.getX()][loc.getY()] = TileTypes::WALL_TILE;
	mpUnitManager->addUnit(Vector2D(loc.getX() * mCellWidth, loc.getY() * mCellHeight), mpWallList);
}
//places a food at grid poistion
void LevelCreation::initFood(Vector2D loc)
{
	mGameSpace[loc.getX()][loc.getY()] = TileTypes::FOOD_TILE;
	mpUnitManager->addUnit(Vector2D(loc.getX() * mCellWidth, loc.getY() * mCellHeight), mpFoodList);
}
//places a speed down powerup at grid position
void LevelCreation::initSpeedDown(Vector2D loc)
{
	mGameSpace[loc.getX()][loc.getY()] = TileTypes::SPEED_DOWN_TILE;
	mpUnitManager->addUnit(Vector2D(loc.getX() * mCellWidth, loc.getY() * mCellHeight), mpSpeedDownList);
}
//places a speed up powerup at a grid postion
void LevelCreation::initSpeedUp(Vector2D loc)
{
	mGameSpace[loc.getX()][loc.getY()] = TileTypes::SPEED_UP_TILE;
	mpUnitManager->addUnit(Vector2D(loc.getX() * mCellWidth, loc.getY() * mCellHeight), mpSpeedUpList);
}
//places a extra points powerup at a grid position
void LevelCreation::initExtraPoints(Vector2D loc)
{
	mGameSpace[loc.getX()][loc.getY()] = TileTypes::EXTRA_POINTS_TILE;
	mpUnitManager->addUnit(Vector2D(loc.getX() * mCellWidth, loc.getY() * mCellHeight), mpExtraPointsList);
}
//places a snake at a grid position
void LevelCreation::initSnake(Vector2D loc)
{
	mGameSpace[loc.getX()][loc.getY()] = TileTypes::SNAKE_TILE;
	mpSnakeUnit->add(new Unit(Vector2D(loc.getX(), loc.getY()), mpSnakeList));
}

//defines various variables based on file data
void LevelCreation::initSettings() 
{
	mSnakeWinLength = mDataMap["winLength"];
	mFoodScore = mDataMap["foodScore"];
	mExtraPointsScore = mDataMap["extraPoints"];
	mPowerUpTimer = mDataMap["powerUpTimer"];
	mSnakeSpeed = mDataMap["speed"];
	mpSnakeUnit->setStartSpeed(mSnakeSpeed);

	for (unsigned int i = 0; i < mBufferKeys.size(); i++) 
	{
		if (mBufferKeys[i] == "BACKGROUND") 
		{
			mBackgroundKey = mBufferKeys[i];
		}
		else if (mBufferKeys[i] == "SNAKE")
		{
			mSnakeKey = mBufferKeys[i];
		}
		else if (mBufferKeys[i] == "FOOD")
		{
			mFoodKey = mBufferKeys[i];
		}
		else if (mBufferKeys[i] == "WALL")
		{
			mWallKey = mBufferKeys[i];
		}
		else if (mBufferKeys[i] == "DOWN")
		{
			mSpeedDownKey = mBufferKeys[i];
		}
		else if (mBufferKeys[i] == "UP")
		{
			mSpeedUpKey = mBufferKeys[i];
		}
		else if (mBufferKeys[i] == "EXTRA")
		{
			mExtraPointsKey = mBufferKeys[i];
		}
	}
}

//checks to see what the snake is colliding with at any given time
void LevelCreation::collisionCheck()
{
	//food collision - incrases score and spawns new food
	/*if (mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] == TileTypes::FOOD_TILE)
	{
		mpUnitManager->removeUnits(Vector2D(mpSnakeUnit->getHead()->getUnitLocX() * mCellWidth, mpSnakeUnit->getHead()->getUnitLocY() * mCellHeight));

		mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] = TileTypes::EMPTY_TILE;

		initSnake(Vector2D(mpSnakeUnit->getTail()->getUnitLocX(), mpSnakeUnit->getTail()->getUnitLocY()));

		//initFood(randomPositionGenerator());

		
		mScore += mFoodScore;

		//checks to see if win length has been achieved and if so resets the level and then loads the next level
		if (mpSnakeUnit->getSnakeSize() >= mSnakeWinLength)
		{
			reset();
			LevelManager::getInstance()->startNextLevel();
		}
	}*/
	//wall and snake collision - resets the level when killed
	if (mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] == TileTypes::SPEED_UP_TILE ||
		mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] == TileTypes::WALL_TILE)
	{
		//prevents instant death at startup
		mFalseDeathCalls += 1;

		while (mFalseDeathCalls >= 14) 
		{
			reset();
			//LevelManager::getInstance()->startLevel(mEndLevelName);
		}
		
	}
	//speed down collision - decrases player speed
	else if (mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] == TileTypes::SPEED_DOWN_TILE)
	{
		mpUnitManager->removeUnits(Vector2D(mpSnakeUnit->getHead()->getUnitLocX() * mCellWidth, mpSnakeUnit->getHead()->getUnitLocY() * mCellHeight));

		mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] = TileTypes::EMPTY_TILE;

		//mpSnakeUnit->setSpeed(0.1);//make 0.1 into mSpeedChange
	}
	//speed up collision - increases player speed
	/*else if (mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] == TileTypes::SPEED_UP_TILE)
	{
		mpUnitManager->removeUnits(Vector2D(mpSnakeUnit->getHead()->getUnitLocX() * mCellWidth, mpSnakeUnit->getHead()->getUnitLocY() * mCellHeight));

		mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] = TileTypes::EMPTY_TILE;

		mpSnakeUnit->setSpeed(-0.1);//make 0.1 into mSpeedChange
	}*/
	//extra points colliison - adds points to score
	else if (mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] == TileTypes::EXTRA_POINTS_TILE)
	{
		mpUnitManager->removeUnits(Vector2D(mpSnakeUnit->getHead()->getUnitLocX() * mCellWidth, mpSnakeUnit->getHead()->getUnitLocY() * mCellHeight));

		mGameSpace[mpSnakeUnit->getHead()->getUnitLocX()][mpSnakeUnit->getHead()->getUnitLocY()] = TileTypes::EMPTY_TILE;

		mScore += mExtraPointsScore;
	}
}

//determines which powerup is placed based on frequency from data file
void LevelCreation::placePowerUps()
{
	for (unsigned int i = 0; i < mPowerUpSpaces.size(); i++)
	{
		if (mPowerUpSpaces[i].type == "speedDown") 
		{
			if ((float)rand() / (float)RAND_MAX < mPowerUpSpaces[i].spawnRate) 
			{
				initSpeedDown(randomPositionGenerator());
				break;
			}
		}
		else if (mPowerUpSpaces[i].type == "speedUp")
		{
			if ((float)rand() / (float)RAND_MAX < mPowerUpSpaces[i].spawnRate)
			{
				initSpeedUp(randomPositionGenerator());
				break;
			}
		}
		else if (mPowerUpSpaces[i].type == "extraPoints")
		{
			if ((float)rand() / (float)RAND_MAX < mPowerUpSpaces[i].spawnRate)
			{
				initExtraPoints(randomPositionGenerator());
				break;
			}
		}
	}

}

//creates the level HUD
void LevelCreation::drawText()
{
	mpSystem->getGraphicsSystem()->writeText(750, 550, mpFont, Color(255, 255, 255), mLevel);
	mpSystem->getGraphicsSystem()->writeText(400, 550, mpFont, Color(255, 255, 255), ("Score: " + to_string(mScore)));
}

//shows the current frame rate
void LevelCreation::drawFrameRate(double frameRate) 
{
	mpSystem->getGraphicsSystem()->writeText(150, 550, mpFont, Color(255, 255, 255), ("FPS: " + to_string(frameRate)));
}

//generates a random Vector2D to be used for random placement
Vector2D LevelCreation::randomPositionGenerator()
{
	Vector2D loc;

	while (mGameSpace[loc.getX()][loc.getY()] != TileTypes::EMPTY_TILE)
	{
		loc.setX((rand() % 14) + 1);//change 15 to mRows
		loc.setY((rand() % 14) + 1);
	}

	return loc;
}

//reads in data from data file
void LevelCreation::readDataFile(string fileName)
{

	if (fileName == "level1.txt") 
	{
		mLevel = "Level 1";
	}
	else if (fileName == "level2.txt")
	{
		mLevel = "Level 2";
	}
	else if (fileName == "level3.txt")
	{
		mLevel = "Level 3";
	}

	ifstream fin;
	fin.open(fileName);

	if (fin.is_open()) 
	{
		string section;
		string key;
		string fileName;
		string powerUpType;
		string tileType;
		float dataValue;
		float spawnFrequency;
		int xPosition;
		int yPosition;
		int numRows;
		int numCols;

		getline(fin, section);

		while (fin >> key && key != mDataStopperString && fin >> dataValue)
		{
			mDataMap.insert(pair<string, float>(key, dataValue));
		}
		
		getline(fin, section);
		getline(fin, section);
		getline(fin, section);

		while (fin >> xPosition && xPosition != mDataStopperInt && fin >> yPosition)
		{
			mSnakePositions.push_back(Vector2D(xPosition, yPosition));
		}

		getline(fin, section);
		getline(fin, section);

		while (fin >> xPosition && xPosition != mDataStopperInt && fin >> yPosition)
		{
			mWallPositions.push_back(Vector2D(xPosition, yPosition));
		}

		getline(fin, section);
		getline(fin, section);

		while (fin >> key && key != mDataStopperString && fin >> fileName && fin >> numRows && fin >> numCols)
		{
			mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + fileName, key);
			mBufferKeys.push_back(key);
		}

		getline(fin, section);
		getline(fin, section);

		while (fin >> powerUpType && powerUpType != mDataStopperString && fin >> tileType && fin >> spawnFrequency) 
		{
			mPowerUpSpaces.push_back(PowerUpSpaces(powerUpType, tileType, spawnFrequency));
		}
	}

	fin.close();
}

void LevelCreation::handleEvent(const Event& theEvent) 
{
	if (theEvent.getType() == GameEvents::CHANGE_DIRECTION_EVENT) 
	{
		auto derChangeEvent = dynamic_cast<const ChangeDirectionEvent&>(theEvent);
		mpSnakeUnit->setDer(derChangeEvent.getX(), derChangeEvent.getY());
		mpSnakeUnit->move(mGameSpace);
	}
}




