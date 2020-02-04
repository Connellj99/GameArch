/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Game.h"

Game* Game::mpGame = nullptr;

Wall::Wall(int size, Point locIn)
{
	GraphicsBuffer* buff = new GraphicsBuffer(size, size);
	Color col(1.0f, 0.0f, 1.0f);
	buff->setColor(&col);
	sprite = new Sprite(buff, 0, 0, size, size);

	loc = locIn;
}

void Wall::draw()
{
	Game::getInstance()->getSystem()->mGraphics.draw(sprite, loc.x, loc.y);
}

void Level::loadLevel()
{
	ifstream f;
	stringstream sstream;

	f.open(file);
	string line;
	int holder;
	bool config = true;
	vector<int> arguments;

	int y = 0;

	while (getline(f, line))
	{
		if (config)
		{
			string term = "";
			for (int i = 0; i < line.size(); i++)
			{
				char current = line[i];
				if (current != ';')
				{
					term += current;
				}
				else
				{
					sstream << term;
					sstream >> holder;
					sstream.clear();
					arguments.push_back(holder);
					term = "";
				}
			}
			sstream << term;
			sstream >> holder;
			sstream.clear();
			arguments.push_back(holder);

			config = false;
			int state = setValues(arguments);
			if (state == 1)
			{
				return;

			}
		}

		else {
			for (int x = 0; x < line.size(); x++)
			{
				char current = line[x];
				if (current == '#')
				{
					walls.push_back(new Wall(blockSize, Point(x * blockSize, y * blockSize)));
				}
			}
			y++;
		}

	}
}

void Level::drawWalls()
{
	for (std::vector<Wall*>::iterator it = walls.begin(); it != walls.end(); ++it) 
	{
		(*it)->draw();
	}
}

Level::~Level()
{
	for (std::vector<Wall*>::iterator it = walls.begin(); it != walls.end(); ++it) 
	{
		delete (*it);
	}
}

int Level::setValues(vector<int> arguments)
{
	if (arguments.size() != 9)
	{
		cout << "INVALID FILE HEADER" << endl;
		return 1;
	}
	
	width = arguments[0];
	height = arguments[1];
	blockSize = arguments[2];
	startLen = arguments[3];
	targetLen = arguments[4];
	pointsPerPower = arguments[5];
	powerFreq = arguments[6];
	start = Point(arguments[7] * blockSize, arguments[8] * blockSize);

	return 0;
}

Game::Game(EventSystem* pEventSystem, int fps) : EventListener(pEventSystem)
{
	getEventSystem()->addListener(MOVE_EVENT, this);
	getEventSystem()->addListener(GROW_EVENT, this);
	getEventSystem()->addListener(GAME_OVER_EVENT, this);
	getEventSystem()->addListener(POWER_UP_EVENT, this);
	getEventSystem()->addListener(CONTINUE_EVENT, this);
	getEventSystem()->addListener(EXIT, this);
	mSystem = new System();
	msPerFrame = (1.0 / fps) * 1000;
}

Game::~Game()
{
	this->cleanUp();
	delete mSystem;
}

void Game::init(int width, int height)
{
	if (!mInit)
	{
		mSystem->init(width, height);
		mGBMan = new GraphicsBufferManager();
		mUnitMan = new UnitManager();
		mInit = true;
	}
}

void Game::cleanUp()
{
	if (mInit)
	{
		mGBMan->clear();
		mUnitMan->clear();

		delete mGBMan;
		delete mUnitMan;

		mSystem->cleanUp();
		delete mpLevelObj;
		mInit = false;
	}
}

void Game::handleEvent(const Event& theEvent) {
	switch (theEvent.getType())
	{
	case MOVE_EVENT:
	{
		const MoveEvent& ev = static_cast<const MoveEvent&>(theEvent);
		Direction dir = Direction(ev.getDir());
		Snake* snake = static_cast<Snake*>((mUnitMan->getUnit(0)));
		snake->setDir(dir);
		break;
	}

	case GROW_EVENT:
	{
		Snake* snake = static_cast<Snake*>((mUnitMan->getUnit(0)));
		snake->addSegment();
		break;
	}

	case GAME_OVER_EVENT:
	{
		if (mLevel != 0 && mLevel != mMaxLevel)
			mPaused = true;
		break;
	}
	
	case POWER_UP_EVENT:
	{
		const PowerUpEvent& ev = static_cast<const PowerUpEvent&>(theEvent);
		PowerUp type = ev.getPower();
		switch (type)
		{
		case SPEED_UP:
			msPerFrame /= 1.2;
			break;

		case SLOW_DOWN:
			msPerFrame *= 1.2;
			break;

		case GET_POINTS:
			if (mLevel != 0 && mLevel != mMaxLevel)
				mScore += 20;
			break;
		case GROW:
			Snake* snake = static_cast<Snake*>((mUnitMan->getUnit(0)));
			snake->addSegment();
			if (mLevel != 0 && mLevel != mMaxLevel)
				mScore += 50;
			break;
		}
		break;
	}

	case CONTINUE_EVENT:
		if (mLevel == 0)
		{
			nextLevel(mLevel + 1);
		}
		else if (mLevel == mMaxLevel)
		{
			getEventSystem()->fireEvent(ExitEvent());
		}
		break;

	case EXIT:
		mExit = true;
		break;
	}
}

void Game::nextLevel(int level)
{
	
	mLevel = level;
	if (mpLevelObj != nullptr)
	{
		delete mpLevelObj;
	}
	mpLevelObj = new Level(mLevel, mLevels[mLevel]);
	mpLevelObj->loadLevel();
	cout << "level Num: " << mpLevelObj->number << endl;

	mSystem->mGraphics.resize(mpLevelObj->width * mpLevelObj->blockSize, mpLevelObj->height * mpLevelObj->blockSize);
	this->reset();
}

void Game::reset()
{

	mUnitMan->clear();
	mSnake = new Snake(mpLevelObj->startLen, mpLevelObj->start, mpLevelObj->blockSize);
	mUnitMan->addUnit(mSnake);
}

void Game::spawnPowerUp()
{
	PowerUp type = PowerUp(rand() % NUM_TYPE);
	GraphicsBuffer * gb;
	switch (type)
	{
	case SPEED_UP:
		gb = mGBMan->getBuffer("greenOrb");
		break;

	case SLOW_DOWN:
		gb = mGBMan->getBuffer("redOrb");
		break;

	case GET_POINTS:
		gb = mGBMan->getBuffer("yellowOrb");
		break;

	case GROW:
		gb = mGBMan->getBuffer("blueOrb");
		break;

	default:
		return;
		break;
	}
	Point pos(rand() % mpLevelObj->width * mpLevelObj->blockSize, rand() % mpLevelObj->height * mpLevelObj->blockSize);
	PowerUpObj * pUp = new PowerUpObj(pos, type, gb, mpLevelObj->blockSize);
	mPowerUps.push_back(pUp);
	mUnitMan->addUnit(pUp);
}

void Game::readGraphicsData(string file)
{
	ifstream f;
	f.open(file);
	string path;
	string name;

	while (f.eof() == false)
	{
		getline(f, path, ';');
		getline(f, name);

		GraphicsBuffer * buff = new GraphicsBuffer(path, false);
		mGBMan->addBuffer(buff, name);

	}
}

void Game::runGame()
{
	Timer time;
	Timer powerTimer;
	MouseState mouse;
	
	this->nextLevel(mLevel);
	readGraphicsData("data.txt");


	powerTimer.start();
	while (!mExit)
	{
		time.start();
		mSystem->clear();	
		mSystem->update();
		if (!mPaused)
			mUnitMan->update(msPerFrame);
		
		if (powerTimer.getElapsedTime() >= mpLevelObj->powerFreq)
		{
			powerTimer.start();
			spawnPowerUp();
			if (mLevel != 0 && mLevel != mMaxLevel && !mPaused)
				mScore -= 1;
		}

		if (mSnake->len() >= mpLevelObj->targetLen)
		{
			cout << "LEVEL UP" << endl;
			if (mLevel < mMaxLevel)
				this->nextLevel(mLevel + 1);
		}

		for (std::vector<Wall*>::iterator it = mpLevelObj->walls.begin(); it != mpLevelObj->walls.end(); ++it)
		{
			if (mSnake->getLoc().isEqual( (*it)->loc))
			{
				Game::getInstance()->getEventSystem()->fireEvent(GameOverEvent());
			}
		}

		for (std::vector<PowerUpObj*>::iterator it = mPowerUps.begin(); it != mPowerUps.end(); ++it)
		{
			if (mSnake->getLoc().isEqual((*it)->getLoc()))
			{
				Game::getInstance()->getEventSystem()->fireEvent(PowerUpEvent((*it)->getPower()));
				mUnitMan->removeUnit(*it);
				mPowerUps.erase(it);
				break;
			}
		}

		mpLevelObj->drawWalls();


		mUnitMan->draw();

		if (mPaused)
		{
			mSystem->mGraphics.writeText("You lose", 100, 100);
			mSystem->mGraphics.writeText("Final Score: " + to_string(mScore), 100, 150);
		}
		if (mLevel == 0)
		{
			mSystem->mGraphics.writeText("WELCOME TO SNAKE", 300, 100);
			mSystem->mGraphics.writeText("Press enter to start the game", 300, 150);


			mSystem->mGraphics.writeText("Blue: Grows the snake", 100, 300);
			mSystem->mGraphics.writeText("Yellow: Adds points to score", 100, 350);
			mSystem->mGraphics.writeText("Green: Speeds up the snake", 100, 400);
			mSystem->mGraphics.writeText("Red: Slows down the snake", 100, 450);


		}
		else if (mLevel == mMaxLevel)
		{
			mSystem->mGraphics.writeText("YOU BEAT THE GAME", 100, 100);
			mSystem->mGraphics.writeText("Final Score: " + to_string(mScore), 100, 150);
		}

		mSystem->mGraphics.writeText("Score: " + to_string(mScore), mSystem->mGraphics.getWindowWidth() - 200, 50);

		mSystem->mGraphics.flip();


		time.sleepUntilElapsed(msPerFrame);
		std::cout << 1000 / time.getElapsedTime() << endl;
	}

	std::cout << "exit" << endl;
}