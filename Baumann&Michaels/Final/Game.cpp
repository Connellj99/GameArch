#include "Game.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "GamePowerupEvent.h"
#include "ApplePowerup.h"
#include "SpeedUpPowerup.h"
#include "SlowDownPowerup.h"
#include "BonusPointsPowerup.h"
#include <iostream>
#include <iomanip>
#include <fstream>
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
	: EventListener(pEventSystem)
{
	pEventSystem->addListener(GAME_MOUSE_CHANGED, this);
	pEventSystem->addListener(GAME_KEY_CHANGED, this);
	pEventSystem->addListener(GAME_POWERUP_EATEN, this);

	mFramesPerSecond = (1.0 / fps) * 1000;
	mpSys = new System(width, height, mFramesPerSecond);
	mHeight = height;
	mWidth = width;
	mMinWidth = 0;
	mMinHeight = 0;
	mMaxWidth = width;
	mMaxHeight = height;

}

void Game::setPlayerSpeed(int speed)
{
	mPlayerSpeed = speed;
}

void Game::init() 
{
	if (!mIsInitted) 
	{
		InitBoilerplateVariables();

		// Init game specific variables
		const int SPRITE_SIZE = 60;

		const string BACKGROUND_BUFFER_NAME = "background";

		const string PLAYER_BUFFER_NAME = "player";
		const string PLAYER_UNIT_NAME = "playerUnit";

		const string BODY_BUFFER_NAME = "body";
		const string BODY_UNIT_NAME = "bodyUnit";

		const string APPLE_BUFFER_NAME = "apple";
		const string APPLE_UNIT_NAME = "appleUnit";

		const string SPEED_UP_BUFFER_NAME = "speedUp";
		const string SPEED_UP_UNIT_NAME = "speedUpUnit";

		const string SLOW_DOWN_BUFFER_NAME = "slowDown";
		const string SLOW_DOWN_UNIT_NAME = "slowDownUnit";

		const string BONUS_BUFFER_NAME = "bonus";
		const string BONUS_UNIT_NAME = "bonusUnit";

		const string WALL_BUFFER_NAME = "wall";
		mWallUnitName = "wallUnit";

		const string WELCOME_SCREEN_BUFFERNAME = "Title";

		const string WIN_SCREEN_BUFFERNAME = "Win";

		const string LOSS_SCREEN_BUFFERNAME = "Loss";

		const string DATA_FILE_NAME = "data.txt";

		loadDataFromFile(DATA_FILE_NAME);

		// Init game specific functions
		createBuffer(BACKGROUND_BUFFER_NAME, mAssetPath + mBackgroundFilename, 800, 600);
		drawBackground(BACKGROUND_BUFFER_NAME, 0, 0);

		createBuffer(WELCOME_SCREEN_BUFFERNAME, mAssetPath + mWelcomeScreenFilename, 800, 600);
		createWelcomeScreen(WELCOME_SCREEN_BUFFERNAME);

		createBuffer(WIN_SCREEN_BUFFERNAME, mAssetPath + mWinScreenFilename, 800, 600);
		createWinScreen(WIN_SCREEN_BUFFERNAME);

		createBuffer(LOSS_SCREEN_BUFFERNAME, mAssetPath + mLossScreenFilename, 800, 600);
		createLossScreen(LOSS_SCREEN_BUFFERNAME);

		createAnimation(PLAYER_BUFFER_NAME, mAssetPath + mPlayerFilename, SPRITE_SIZE);
		createAnimation(WALL_BUFFER_NAME, mAssetPath + mWallFilename, SPRITE_SIZE);
		createAnimation(BODY_BUFFER_NAME, mAssetPath + mBodyFilename, SPRITE_SIZE);
		createAnimation(APPLE_BUFFER_NAME, mAssetPath + mAppleFilename, SPRITE_SIZE);
		createAnimation(SPEED_UP_BUFFER_NAME, mAssetPath + mSpeedUpFilename, SPRITE_SIZE);
		createAnimation(SLOW_DOWN_BUFFER_NAME, mAssetPath + mSlowDownFilename, SPRITE_SIZE);
		createAnimation(BONUS_BUFFER_NAME, mAssetPath + mBonusFilename, SPRITE_SIZE);

		createUnit(PLAYER_UNIT_NAME);
		createUnit(mWallUnitName);
		createUnit(BODY_UNIT_NAME);
		createUnit(APPLE_UNIT_NAME);
		createUnit(SPEED_UP_UNIT_NAME);
		createUnit(SLOW_DOWN_UNIT_NAME);
		createUnit(BONUS_UNIT_NAME);

		addAnimationToUnit(PLAYER_UNIT_NAME, PLAYER_BUFFER_NAME);
		addAnimationToUnit(mWallUnitName, WALL_BUFFER_NAME);
		addAnimationToUnit(BODY_UNIT_NAME, BODY_BUFFER_NAME);
		addAnimationToUnit(APPLE_UNIT_NAME, APPLE_BUFFER_NAME);
		addAnimationToUnit(SPEED_UP_UNIT_NAME, SPEED_UP_BUFFER_NAME);
		addAnimationToUnit(SLOW_DOWN_UNIT_NAME, SLOW_DOWN_BUFFER_NAME);
		addAnimationToUnit(BONUS_UNIT_NAME, BONUS_BUFFER_NAME);

		loadLevelsFromFiles();

		updateDataFromCurrentLevel();

		makeControllable(PLAYER_UNIT_NAME, BODY_UNIT_NAME);
		addRandomlySpawningApple(APPLE_UNIT_NAME);
		addRandomlySpawningSpeedUp(SPEED_UP_UNIT_NAME);
		addRandomlySpawningSlowDown(SLOW_DOWN_UNIT_NAME);
		addRandomlySpawningBonusPoints(BONUS_UNIT_NAME);

	}
	
}

void Game::loadLevelsFromFiles()
{
	for (int i = 1; i <= mNumberOfLevels; i++)
	{
		string filename = "level" + to_string(i) + ".txt";
		fstream dataFile(filename, ios_base::in);
		string speedRaw, startSegmentsRaw, maxLengthRaw, foodPointsRaw, 
			bonusScoreRaw, appleFrequencyRaw, speedUpFrequencyRaw, 
			slowDownFrequencyRaw, bonusFrequencyRaw, rawTitle;

		int playerSpeed, startSegments, maxLength, foodPoints,
			bonusScore, appleFrequency, speedUpFrequency, 
			slowDownFrequency, bonusFrequency;

		getline(dataFile, speedRaw);
		playerSpeed = stoi(speedRaw.substr(14));

		getline(dataFile, startSegmentsRaw);
		startSegments = stoi(startSegmentsRaw.substr(23));

		getline(dataFile, maxLengthRaw);
		maxLength = stoi(maxLengthRaw.substr(12));

		getline(dataFile, foodPointsRaw);
		foodPoints = stoi(foodPointsRaw.substr(17));

		getline(dataFile, bonusScoreRaw);
		bonusScore = stoi(bonusScoreRaw.substr(14));

		getline(dataFile, appleFrequencyRaw); 
		appleFrequency = stoi(appleFrequencyRaw.substr(17));

		getline(dataFile, speedUpFrequencyRaw);
		speedUpFrequency = stoi(speedUpFrequencyRaw.substr(20));

		getline(dataFile, slowDownFrequencyRaw);
		slowDownFrequency = stoi(slowDownFrequencyRaw.substr(21));

		getline(dataFile, bonusFrequencyRaw);
		bonusFrequency = stoi(bonusFrequencyRaw.substr(17));

		getline(dataFile, rawTitle);
		rawTitle = rawTitle.substr(7);

		Level* tempLevel = new Level(playerSpeed, startSegments, maxLength, foodPoints, bonusScore, rawTitle);
		mpLevelManager->addLevel(tempLevel);

		tempLevel->setAppleFrequency(appleFrequency);
		tempLevel->setSpeedUpFrequency(speedUpFrequency);
		tempLevel->setSlowDownFrequency(slowDownFrequency);
		tempLevel->setBonusFrequency(bonusFrequency);

		string numWallsRaw;
		int numWalls;
		getline(dataFile, numWallsRaw);
		numWalls = stoi(numWallsRaw.substr(11));

		for (int j = 0; j < numWalls; j++)
		{
			string xRaw, yRaw;
			int x, y;

			getline(dataFile, xRaw);
			x = stoi(xRaw.substr(3));

			getline(dataFile, yRaw);
			y = stoi(yRaw.substr(3));

			int* coords = new int[2];
			coords[0] = x;
			coords[1] = y;

			tempLevel->addWallLocation(coords);

		}
	}
}

void Game::loadDataFromFile(string filePath)
{
	
	fstream dataFile(filePath, ios_base::in);
	string assetPathRaw, backgroundPathRaw, playerPathRaw, wallPathRaw,
		bodyPathRaw, applePathRaw, speedUpPathRaw, slowDownPathRaw, bonusPathRaw,
		welcomeScreenPathRaw, winScreenPathRaw, lossScreenPathRaw, numLevelsRaw;

	getline(dataFile, assetPathRaw);
	mAssetPath = assetPathRaw.substr(12);

	getline(dataFile, backgroundPathRaw);
	mBackgroundFilename = backgroundPathRaw.substr(21);

	getline(dataFile, playerPathRaw);
	mPlayerFilename = playerPathRaw.substr(17);

	getline(dataFile, wallPathRaw);
	mWallFilename = wallPathRaw.substr(15);

	getline(dataFile, bodyPathRaw);
	mBodyFilename = bodyPathRaw.substr(15);

	getline(dataFile, applePathRaw);
	mAppleFilename = applePathRaw.substr(16); 

	getline(dataFile, speedUpPathRaw);
	mSpeedUpFilename = speedUpPathRaw.substr(19); 

	getline(dataFile, slowDownPathRaw);
	mSlowDownFilename = slowDownPathRaw.substr(20); 

	getline(dataFile, bonusPathRaw);
	mBonusFilename = bonusPathRaw.substr(16); 

	getline(dataFile, welcomeScreenPathRaw);
	mWelcomeScreenFilename = welcomeScreenPathRaw.substr(25); 

	getline(dataFile, winScreenPathRaw);
	mWinScreenFilename = winScreenPathRaw.substr(21); 

	getline(dataFile, lossScreenPathRaw);
	mLossScreenFilename = lossScreenPathRaw.substr(22); 

	getline(dataFile, numLevelsRaw);
	mNumberOfLevels = stoi(numLevelsRaw.substr(18));
}

void Game::createBoundariesFromFile(string unitName, string filePath)
{
	fstream dataFile(filePath, ios_base::in);
	int minWidth, maxWidth, minHeight, maxHeight, increments, offset;
	dataFile >> minWidth >> maxWidth >> minHeight >> maxHeight >> increments >> offset;
	mpUnitManager->addBoundarieBox(unitName, minWidth, maxWidth, minHeight, maxHeight, increments, offset);
	mMinWidth = minWidth;
	mMinHeight = minHeight;
	mMaxWidth = maxWidth;
	mMaxHeight = maxHeight;
}

void Game::createLossScreen(const std::string &LOSS_SCREEN_BUFFERNAME)
{
	mLossScreen = mSprites.find(LOSS_SCREEN_BUFFERNAME)->second;
}

void Game::createWinScreen(const std::string &WIN_SCREEN_BUFFERNAME)
{
	mWinScreen = mSprites.find(WIN_SCREEN_BUFFERNAME)->second;
}

void Game::createWelcomeScreen(const std::string &WELCOME_SCREEN_BUFFERNAME)
{
	mTitleScreen = mSprites.find(WELCOME_SCREEN_BUFFERNAME)->second;
}

void Game::updateDataFromCurrentLevel()
{
	mCurrentLevel = mpLevelManager->getLevelAtCurrentIndex();
	resetPlayerPosition();
	resetPlayerDirection();
	resetWallLocations();
	loadNewWalls();
	mAppleFrequency = mCurrentLevel->getAppleFrequency();
	mSpeedUpFrequency = mCurrentLevel->getSpeedUpFrequency();
	mSlowDownFrequency = mCurrentLevel->getSlowDownFrequency();
	mBonusFrequency = mCurrentLevel->getBonusFrequency();

	mPlayerSpeed = mCurrentLevel->getPlayerSpeed();
	mAppleScore = mCurrentLevel->getFoodPoints();
	mBonusScore = mCurrentLevel->getBonusScore();
	mpUnitManager->increasePlayerLengthAndResetBody(mCurrentLevel->getPlayerStartingSegments());
	mpUnitManager->clearBodyStorage();
}

void Game::checkPlayerLength()
{
	if (mpUnitManager->getLengthOfPlayer() > mCurrentLevel->getMaxSegmentLength())
	{
		int gameWon = mpLevelManager->endLevel();
		if (gameWon)
		{
			gameWin();
		}
		else 
		{
			updateDataFromCurrentLevel();
		}
		
	}
}

void Game::gameWin()
{
	mGameState = 2;
	resetGame();
}

void Game::resetGame()
{
	mpLevelManager->goToStartLevel();
	resetPlayerPosition();
	resetPlayerDirection();
	updateDataFromCurrentLevel();
}

void Game::InitBoilerplateVariables()
{
	mpPerformanceTracker = new PerformanceTracker;
	mpUnitManager = new UnitManager();
	mpGBManager = new GraphicsBufferManager();
	mpPowerupManager = new PowerupManager(mpUnitManager, 60, mWidth, mHeight, 30);
	mpLevelManager = new LevelManager();
	mainFont = new Font(20);
	mpCurrentMousePos = new int[2];
	mpCurrentMousePos[0] = mWidth / 2;
	mpCurrentMousePos[1] = mHeight / 2;

	mpPlayerStartingPos = new int[2];
	resetPlayerPosition();

	mpPlayerDirection = new int[2];
	resetPlayerDirection();

	mPlayerSpeed = 5;

	mpSys->init();
	mIsCleanedUp = false;
	mIsInitted = true;
}

void Game::resetPlayerDirection()
{
	mpPlayerDirection[0] = 0;
	mpPlayerDirection[1] = 5;
}

void Game::resetPlayerPosition()
{
	mpPlayerStartingPos[0] = mWidth / 2;
	mpPlayerStartingPos[1] = mHeight / 2;
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
	case GAME_POWERUP_EATEN:
		handlePowerupEvent(theEvent);
		break;
	}
}

void Game::handleMouseEvent(const Event& theEvent)
{
	const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
	if (mouseEvent.getButtonType() == MOUSE_OVER)
	{
		updateMouseLocation(mouseEvent.getLocation());
	}
	else if (mouseEvent.getButtonType() == LEFT_MOUSE)
	{
		updateMouseLocation(mouseEvent.getLocation());
		mMouseDown = !mMouseDown;
	}
	else if (mouseEvent.getButtonType() == RIGHT_MOUSE)
	{
		updateMouseLocation(mouseEvent.getLocation());
		mRightMouseDown = !mRightMouseDown;
	}
}

void Game::handlePowerupEvent(const Event& theEvent)
{
	const PowerupEvent& powerupEvent = static_cast<const PowerupEvent&>(theEvent);
	if (powerupEvent.getButtonType() == SLOW_DOWN)
	{
		if (mPlayerSpeed > 1) 
		{
			mPlayerSpeed -= 1;
		}
	}
	else if (powerupEvent.getButtonType() == SPEED_UP)
	{
		mPlayerSpeed += 1;
	}
	else if (powerupEvent.getButtonType() == BONUS_POINTS)
	{
		mpUnitManager->increasePlayerLengthBy(mBonusScore);
	}
	else if (powerupEvent.getButtonType() == APPLE_EATEN)
	{
		mpUnitManager->increasePlayerLengthBy(mAppleScore);
	}
}

void Game::updateMouseLocation(Vector2D newMouseLocation)
{
	mpCurrentMousePos[0] = newMouseLocation.getX();
	mpCurrentMousePos[1] = newMouseLocation.getY();
}

void Game::handleKeyEvent(const Event& theEvent)
{
	const KeyEvent& keyEvent = static_cast<const KeyEvent&>(theEvent);
	switch (keyEvent.getButtonType())
	{
	case W_KEY:
		if (mpPlayerDirection[1] != -mPlayerSpeed && mpPlayerDirection[1] != mPlayerSpeed)
		{
			updatePlayerDirection(0, -mPlayerSpeed);
		}
		break;
	case A_KEY:
		if (mpPlayerDirection[0] != -mPlayerSpeed && mpPlayerDirection[0] != mPlayerSpeed)
		{
			updatePlayerDirection(-mPlayerSpeed, 0);
		}
		break;
	case S_KEY:
		if (mpPlayerDirection[1] != mPlayerSpeed && mpPlayerDirection[1] != -mPlayerSpeed)
		{
			updatePlayerDirection(0, mPlayerSpeed);
		}
		break;
	case D_KEY:
		if (mpPlayerDirection[0] != mPlayerSpeed && mpPlayerDirection[0] != -mPlayerSpeed)
		{
			updatePlayerDirection(mPlayerSpeed, 0);
		}
		break;
	case ENTER_KEY:
		mSwapNow = true;
		break;
	case F_KEY:
		mSpeedUp = System::eventType::SpeedUp;
		break;
	case SPACE_KEY:
		if (mGameState == 0)
		{
			startGame();
		}
		else if (mGameState == 2 || mGameState == 3) 
		{
			gameTitle();
		}
		break;
	case ESCAPE_KEY:
		mExitNow = true;
		break;
	}
}

void Game::gameTitle()
{
	mGameState = 0;
}

void Game::startGame()
{
	mGameState++;
	resetWallLocations();
	loadNewWalls();
}

void Game::resetWallLocations()
{
	mpUnitManager->clearWallStorage();
}

void Game::loadNewWalls()
{
	vector<int*> newWalls = mpLevelManager->getLevelAtCurrentIndex()->getWallLocations();
	for (auto i : newWalls)
	{
		mpUnitManager->addWallAtPosition(mWallUnitName, i[0], i[1]);
	}
}

void Game::updatePlayerDirection(int x, int y)
{
	mpPlayerDirection[0] = x;
	mpPlayerDirection[1] = y;
}

void Game::makeControllable(string unitName, string bodyName)
{
	mpUnitManager->addPlayer(unitName, bodyName);
}
void Game::createWallFromFile(string unitName, string filePath, int offset)
{
	fstream dataFile(filePath, ios_base::in);
	int startX, startY, endX, endY;
	dataFile >> startX >> startY >> endX >> endY;
	mpUnitManager->addWall(unitName, startX, startY, endX, endY, offset);
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

void Game::addRandomlySpawningApple(string unitName)
{
	
	Powerup* newApple = new ApplePowerup(unitName, mpUnitManager->getUnit(unitName), mAppleFrequency, mpUnitManager);
	mpPowerupManager->addPowerupToBuffer(newApple);
	mAppleName = unitName;
}

void Game::addRandomlySpawningSpeedUp(string unitName)
{
	Powerup* newSpeedUp = new SpeedUpPowerup(unitName, mpUnitManager->getUnit(unitName), mSpeedUpFrequency, mpUnitManager);
	mpPowerupManager->addPowerupToBuffer(newSpeedUp);
	mSpeedUpName = unitName;
}

void Game::addRandomlySpawningSlowDown(string unitName)
{
	
	Powerup* newSlowDown = new SlowDownPowerup(unitName, mpUnitManager->getUnit(unitName), mSlowDownFrequency, mpUnitManager);
	mpPowerupManager->addPowerupToBuffer(newSlowDown);
	mSlowDownName = unitName;
}

void Game::addRandomlySpawningBonusPoints(string unitName)
{
	Powerup* newBonusPoints = new BonusPointsPowerup(unitName, mpUnitManager->getUnit(unitName), mBonusFrequency, mpUnitManager);
	mpPowerupManager->addPowerupToBuffer(newBonusPoints);
	mBonusPointsName = unitName;
}

void Game::createWallAtLocation(string unitName, int xPos, int yPos)
{
	mpUnitManager->addWallAtPosition(unitName, xPos, yPos);
}

void Game::doLoop()
{
	const int MOUSE_OFFSET = 30;
	const int BOUNDARY_OFFSET = 30;
	const float UNIT_SCALE = 1.0;
	double lastTime = 0;

	while (true) 
	{
		beginTimingAndTrackingLoop();
		if (mGameState == 1)
		{
			playMainGameLoop(BOUNDARY_OFFSET, lastTime, UNIT_SCALE, MOUSE_OFFSET);
		}
		else if (mGameState == 0)
		{
			drawTitleScreen(UNIT_SCALE);
			flipSystemGraphicsBuffer();
		}
		else if (mGameState == 2)
		{
			drawWinScreen(UNIT_SCALE);
			flipSystemGraphicsBuffer();
		}
		else if (mGameState == 3)
		{
			drawLossScreen(UNIT_SCALE);
			flipSystemGraphicsBuffer();
		}
		
		

		waitForInputOrEndOfFrame();

		displayFPS();

		stopTrackingLoop();
		if (mExitNow) 
		{
			break;
		}
	}
}

void Game::drawLossScreen(const float &UNIT_SCALE)
{
	mpSys->draw(0, 0, mLossScreen, UNIT_SCALE);
}

void Game::drawWinScreen(const float &UNIT_SCALE)
{
	mpSys->draw(0, 0, mWinScreen, UNIT_SCALE);
}

void Game::drawTitleScreen(const float &UNIT_SCALE)
{
	mpSys->draw(0, 0, mTitleScreen, UNIT_SCALE);
}


void Game::playMainGameLoop(const int &BOUNDARY_OFFSET, double &lastTime, const float &UNIT_SCALE, const int &MOUSE_OFFSET)
{
	placePlayerAtNewLocation();

	updatePlayerPositionBasedOnDirection(BOUNDARY_OFFSET);

	updateUnitAnimationsBasedOnElapsedTime(lastTime, UNIT_SCALE, MOUSE_OFFSET);

	mpPowerupManager->updatePowerupSpawning(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER));

	mpPowerupManager->checkAllPowerupsForCollisionWithPlayer();

	checkPlayerLength();

	flipSystemGraphicsBuffer();

	drawBackgroundImages(UNIT_SCALE);
}

void Game::flipSystemGraphicsBuffer()
{
	mpSys->flip();
}

void Game::stopTrackingLoop()
{
	mpPerformanceTracker->stopTracking(mLOOP_TRACKER);
}

void Game::beginTimingAndTrackingLoop()
{
	mpPerformanceTracker->clearTracker(mLOOP_TRACKER);
	mpPerformanceTracker->startTracking(mLOOP_TRACKER);

	mTimer.start();
}

void Game::displayFPS()
{
	float currentFPS = 1 / (mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER) / 1000);
	std::cout << endl << "loop time: " << setprecision(4) << currentFPS << " FPS";
	mpSys->writeText(50, 30, mainFont, 5, 5, 5, "FPS: " + to_string(currentFPS).substr(0,5));
	mpSys->writeText(260, 30, mainFont, 5, 5, 5, mpLevelManager->getCurrentLevelTitle());
	mpSys->writeText(600, 30, mainFont, 5, 5, 5, "Score: " + to_string(mpUnitManager->getLengthOfPlayer()) + " / " + to_string(mCurrentLevel->getMaxSegmentLength() + 1));
}

void Game::waitForInputOrEndOfFrame()
{
	while (mTimer.getElapsedTime() < mFramesPerSecond)
	{
		mpSys->waitForEvent();
	}

	mTimer.sleepUntilElapsed(mFramesPerSecond);
}

void Game::updateUnitAnimationsBasedOnElapsedTime(double &lastTime, const float &UNIT_SCALE, const int &MOUSE_OFFSET)
{
	lastTime += mTimer.getElapsedTime();

	mpUnitManager->update(lastTime);
	mpUnitManager->draw(mpSys, UNIT_SCALE, MOUSE_OFFSET);
}

void Game::instantiateUnitsOnMouseDown(const int &MOUSE_OFFSET)
{
	if (mMouseDown)
	{
		mpUnitManager->instantiateAtMouse(mMouseDown, mpCurrentMousePos, mpSys, MOUSE_OFFSET);
	}
}

void Game::updatePlayerPositionBasedOnDirection(const int &BOUNDARY_OFFSET)
{
	if (mpPlayerStartingPos[0] + mpPlayerDirection[0] <= mMaxWidth - BOUNDARY_OFFSET && mpPlayerStartingPos[0] + mpPlayerDirection[0] > mMinWidth + BOUNDARY_OFFSET)
	{
		mpPlayerStartingPos[0] += mpPlayerDirection[0];
	}
	else 
	{
		gameOver();
	}
	if (mpPlayerStartingPos[1] + mpPlayerDirection[1] <= mMaxHeight - BOUNDARY_OFFSET && mpPlayerStartingPos[1] + mpPlayerDirection[1] > mMinHeight + BOUNDARY_OFFSET)
	{
		mpPlayerStartingPos[1] += mpPlayerDirection[1];
	}
	else
	{
		gameOver();
	}
	if (mpUnitManager->playerCollidedWithWall(60))
	{
		gameOver();
	}
}

void Game::gameOver()
{
	mGameState = 3;
	resetGame();
	resetWallLocations();
}

void Game::placePlayerAtNewLocation()
{
	int playerCollided = mpUnitManager->placePlayer(mpPlayerStartingPos);
	if (playerCollided)
	{
		gameOver();
	}
}

void Game::updateLocationsAndDrawAllUnits(const float &UNIT_SCALE, const int &MOUSE_OFFSET)
{
	for (auto i : mAlwaysAnimate)
	{
		i->updateLocation(mpCurrentMousePos[0], mpCurrentMousePos[1]);
		i->draw(mpSys, UNIT_SCALE, MOUSE_OFFSET);
	}
}

void Game::speedUpUnitsOnKeyPressed()
{
	switch (mSpeedUp)
	{
	case System::eventType::SpeedUp:
		for (auto i : mSwapOnEnter)
		{
			i->speedUp();
		}
		mSpeedUp = 0;
		break;
	case System::eventType::SlowDown:
		for (auto i : mSwapOnEnter)
		{
			i->slowDown();
		}
		mSpeedUp = 0;
		break;
	}
}

void Game::swapUnitsOnEnter()
{
	if (mSwapNow)
	{
		for (auto i : mSwapOnEnter)
		{
			i->incrementAnimation();
		}
		mSwapNow = false;

		mpUnitManager->incrementLastSpriteAnimation();
	}
}

void Game::drawBackgroundImages(const float &UNIT_SCALE)
{
	for (auto i : mAlwaysDraw)
	{
		mpSys->draw(0, 0, i, UNIT_SCALE);
	}
}

void Game::removeAtMouseCoordsIfRightMouseDown()
{
	if (mRightMouseDown) {
		mpUnitManager->removeAtCoords(mpCurrentMousePos);
	}
}

void Game::cleanup() 
{

	if (!mIsCleanedUp) 
	{

		delete mainFont;

		delete mpSys;

		delete mpLevelManager;

		delete mpCurrentMousePos;

		delete mpPlayerStartingPos;

		delete  mpPlayerUpdatedPos;

		delete mpPlayerDirection;

		delete mpPerformanceTracker;

		delete mpPowerupManager;

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