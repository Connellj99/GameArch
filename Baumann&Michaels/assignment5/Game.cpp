#include "Game.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include <iostream>
#include <iomanip>
using namespace std;

Game* Game::mpGameInstance = nullptr;

Game::Game()
{
}

Game::Game(EventSystem* pEventSystem)
	:EventListener(pEventSystem)
{
}

Game::Game(EventSystem* pEventSystem, int width, int height, float fps)
	:EventListener(pEventSystem)
{
	pEventSystem->addListener(GAME_MOUSE_CHANGED, this);
	pEventSystem->addListener(GAME_KEY_CHANGED, this);

	mFramesPerSecond = (1.0 / fps) * 1000;
	mpSys = new System(width, height, mFramesPerSecond);
	mHeight = height;
	mWidth = width;
}

void Game::init() 
{
	if (!mIsInitted) 
	{
		// Init boilerplate variables
		mpPerformanceTracker = new PerformanceTracker;
		mpUnitManager = new UnitManager();
		mpGBManager = new GraphicsBufferManager();
		mpCurrentMousePos = new int[2];
		mpCurrentMousePos[0] = mWidth / 2;
		mpCurrentMousePos[1] = mHeight / 2;
		mpSys->init();
		mIsCleanedUp = false;
		mIsInitted = true;

		// Init game specific variables
		const string WOODS_FILENAME = "woods.png";
		const string WOODS_BUFFER_NAME = "woods";
		const int SPRITE_SIZE = 60;
		const string SMURFS_UNIT_NAME = "theSmurf";
		const string SMURFS_FILENAME = "smurf_sprites.png";
		const string SMURFS_BUFFER_NAME = "smurfs";
		const string DEAN_FILENAME = "dean_sprites.png";
		const string DEAN_BUFFER_NAME = "deans";
		const string PLAYER_UNIT_NAME = "player";
		const string PLAYER_BUFFER_NAME = "playerBuff";

		float* lowerBounds = new float[2];
		lowerBounds[0] = 500;
		lowerBounds[1] = 500;

		float* upperBounds = new float[2];
		upperBounds[0] = 100;
		upperBounds[1] = 100;

		// Init game specific functions
		createBuffer(WOODS_BUFFER_NAME, WOODS_FILENAME, 800, 600);
		drawBackground(WOODS_BUFFER_NAME, 0, 0);

		createAnimation(SMURFS_BUFFER_NAME, SMURFS_FILENAME, SPRITE_SIZE);
		createAnimation(DEAN_BUFFER_NAME, DEAN_FILENAME, SPRITE_SIZE);

		createUnit(SMURFS_UNIT_NAME);

		createAnimation(PLAYER_BUFFER_NAME, SMURFS_FILENAME, SPRITE_SIZE);

		createPlayerAtCoords(PLAYER_BUFFER_NAME, 200, 200, 10);

		setHomeBaseBounds(lowerBounds, upperBounds);

		addAnimationToUnit(SMURFS_UNIT_NAME, SMURFS_BUFFER_NAME);
		addAnimationToUnit(SMURFS_UNIT_NAME, DEAN_BUFFER_NAME);

		swapOnEnter(SMURFS_UNIT_NAME);
		createOnMouseDown(SMURFS_UNIT_NAME);
	}
	
}

void Game::createPlayerAtCoords(const std::string &PLAYER_BUFFER_NAME, int xLoc, int yLoc, float speed)
{
	mpPlayer = new Player(xLoc, yLoc, speed);

	mpPlayer->addAnimation(mAnimations.find(PLAYER_BUFFER_NAME)->second);

	mpUnitManager->addToStorage(mpPlayer);
}

void Game::setHomeBaseBounds(float* lowerBounds, float* upperBounds)
{
	mpPlayer->setBounds(lowerBounds, upperBounds);
}

void Game::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case GAME_MOUSE_CHANGED:
		handleMouseEvent(theEvent);
		break;
	case GAME_KEY_CHANGED:
		handleKeyEvent(theEvent);
		break;
	}
}

void Game::handleMouseEvent(const Event& theEvent)
{
	const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
	if (mouseEvent.getButtonType() == MOUSE_OVER)
	{
		Vector2D tempVec = mouseEvent.getLocation();
		mpCurrentMousePos[0] = tempVec.getX();
		mpCurrentMousePos[1] = tempVec.getY();
	}
	else if (mouseEvent.getButtonType() == LEFT_MOUSE)
	{
		Vector2D tempVec = mouseEvent.getLocation();
		mpCurrentMousePos[0] = tempVec.getX();
		mpCurrentMousePos[1] = tempVec.getY();
		mMouseDown = !mMouseDown;
	}
	else if (mouseEvent.getButtonType() == RIGHT_MOUSE)
	{
		Vector2D tempVec = mouseEvent.getLocation();
		mpCurrentMousePos[0] = tempVec.getX();
		mpCurrentMousePos[1] = tempVec.getY();
		mRightMouseDown = !mRightMouseDown;
	}
}

void Game::handleKeyEvent(const Event& theEvent)
{
	const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);
	switch (keyEvent.getButtonType())
	{
	case ENTER_KEY:
		mSwapNow = true;
		break;
	case F_KEY:
		mSpeedUp = System::eventType::SpeedUp;
		break;
	case S_KEY:
		mSpeedUp = System::eventType::SlowDown;
		break;
	case SPACE_KEY:
		mpUnitManager->swapFrozen();
		break;
	case ESCAPE_KEY:
		mExitNow = true;
		break;

	case UP_KEY:
		mpPlayer->mVectY = -1 * mpPlayer->getSpeed();
		break;

	case LEFT_KEY:
		mpPlayer->mVectX = -1 * mpPlayer->getSpeed();
		break;

	case DOWN_KEY:
		mpPlayer->mVectY = mpPlayer->getSpeed();
		break;

	case RIGHT_KEY:
		mpPlayer->mVectX = mpPlayer->getSpeed();
		break;

	case UP_KEY_UP:
		mpPlayer->mVectY = 0;
		break;

	case LEFT_KEY_UP:
		mpPlayer->mVectX = 0;
		break;

	case DOWN_KEY_UP:
		mpPlayer->mVectY = 0;
		break;

	case RIGHT_KEY_UP:
		mpPlayer->mVectX = 0;
		break;
	}
}

void Game::createBuffer(string bufferName, string filename, int width, int height)
{ 
	GraphicsBuffer* newGb = new GraphicsBuffer(filename);
	mpGBManager->addBuffer(newGb);

	Sprite* newGbSprite = new Sprite(newGb, 0, 0, width, height);
	mSprites.insert({ bufferName, newGbSprite });
}

void Game::createAnimation(string animationName, string filename, int dimensions) 
{
	GraphicsBuffer* newGb = new GraphicsBuffer(filename);
	vector<GraphicsBuffer*> targetGb;
	mpGBManager->addBuffer(newGb);
	Animation* newAnim = mpSys->createAnimation(newGb, targetGb, dimensions);
	for (auto i : targetGb)
	{
		mpGBManager->addBuffer(i);
	}
	mAnimations.insert({ animationName, newAnim });
}

void Game::createUnit(string unitName) 
{
	Unit* newUnit = new Unit();
	mpUnitManager->addUnit(unitName, newUnit);
}

void Game::addAnimationToUnit(string unitName, string animationName) 
{
	Unit* unitToChange = mpUnitManager->getUnit(unitName);
	unitToChange->addAnimation(mAnimations.find(animationName)->second);
}

void Game::drawBackground(string bufferName, int x, int y, float scale)
{
	Sprite* newSprite = mSprites.find(bufferName)->second;
	mAlwaysDraw.push_back(newSprite);
}

void Game::swapOnEnter(string unitName)
{
	mSwapOnEnter.push_back(mpUnitManager->getUnit(unitName));
}

void Game::drawUnitAtMouse(string unitName)
{
	mAlwaysAnimate.push_back(mpUnitManager->getUnit(unitName));
}

void Game::createOnMouseDown(string unitName)
{
	mpUnitManager->addAlwaysCreate(unitName);
}

void Game::InstantiateAtMouse(Unit* unitName, int offset)
{
	Unit* newInstance = new Unit(unitName, mpCurrentMousePos);
	newInstance->draw(mpSys, 1, offset);
	mpUnitManager->addToStorage(newInstance);
}

void Game::doLoop() 
{
	const int MOUSE_OFFSET = 30;
	const float UNIT_SCALE = 1.0;
	mTimer.start();
	double lastTime = 0;
	while (true) 
	{
		mpPerformanceTracker->clearTracker(mLOOP_TRACKER);
		mpPerformanceTracker->startTracking(mLOOP_TRACKER);

		mTimer.start();

		//Draw background image(s)
		for (auto i : mAlwaysDraw) 
		{
			mpSys->draw(0, 0, i, UNIT_SCALE);
		}

		for (auto i : mAlwaysAnimate) 
		{
			i->updateLocation(mpCurrentMousePos[0], mpCurrentMousePos[1]);
			i->draw(mpSys, UNIT_SCALE, MOUSE_OFFSET);
		}
		

		lastTime += mTimer.getElapsedTime();
		
		mpUnitManager->update(lastTime);
		mpUnitManager->draw(mpSys, UNIT_SCALE, MOUSE_OFFSET);

		mpSys->flip();

		//Waits until we have input to do anything. If no input is found, waits until the end of the frame.
		while (mTimer.getElapsedTime() < mFramesPerSecond) 
		{
			mpSys->waitForEvent();
		}

		mTimer.sleepUntilElapsed(mFramesPerSecond);

		mpPerformanceTracker->stopTracking(mLOOP_TRACKER);
		std::cout << endl << "loop time: " << setprecision(4) << 1/(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER)/1000) << " FPS";

		if (mExitNow) 
		{
			break;
		}
	}
}

void Game::cleanup() 
{

	if (!mIsCleanedUp) 
	{

		delete mpSys;

		delete mpCurrentMousePos;

		delete mpPerformanceTracker;

		delete mpUnitManager;

		for (auto const& i : mSprites)
		{
			delete i.second;
		}
		
		delete mpGBManager;

		mIsCleanedUp = true;
		mIsInitted = false;

		delete(this);

	}
	
}

void Game::createInstance(EventSystem* pEventSystem, int width, int height, int FPS)
{
	if (mpGameInstance == nullptr) 
	{
		mpGameInstance = new Game(pEventSystem, width, height, FPS);
	}
}

Game* Game::getInstance() 
{
	if (mpGameInstance != nullptr) 
	{
		return mpGameInstance;
	}
	return nullptr;
}

void Game::cleanupInstance() 
{
	if (mpGameInstance != nullptr) 
	{
		mpGameInstance = nullptr;
	}
}

Game::~Game() 
{
	cleanup();
}