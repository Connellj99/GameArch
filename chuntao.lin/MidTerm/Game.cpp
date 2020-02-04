#include "Game.h"
#include "Unit.h"
#include "Animation.h"
#include "EventListener.h"

Game * Game::mpsGameObject = nullptr;

// This function is the default constructor for this class
Game::Game()
{
	// Create the system object
	mpSystem = new System();

	//Create the input system
	mpInputSys = new InputSystem();
}

//this constructor takes the event system
Game::Game(EventSystem* passedEventSystem)
	:EventListener(passedEventSystem)
{

	// Listen to all events that need to be listened for
	
	//Listeners for game status
	passedEventSystem->addListener((EventType)EXIT, this);
	passedEventSystem->addListener((EventType)START, this);
	passedEventSystem->addListener((EventType)RESTART, this);

	//Listeners for units
	passedEventSystem->addListener((EventType)CREATE, this);
	passedEventSystem->addListener((EventType)KILL, this);
	passedEventSystem->addListener((EventType)TOGGLE_ANIMATION, this);
	passedEventSystem->addListener((EventType)FLIP_ANIMATIONS, this);

	//Listeners for user movements/arrows
	passedEventSystem->addListener((EventType)MOVE_LEFT, this);
	passedEventSystem->addListener((EventType)MOVE_RIGHT, this);
	passedEventSystem->addListener((EventType)MOVE_UP, this);
	passedEventSystem->addListener((EventType)MOVE_DOWN, this);

	// Create the system object
	mpSystem = new System();

	// Create the input system object
	mpInputSys= new InputSystem();
}



// This function is the destructor for this class
Game::~Game()
{
	if ( mIsDisplaying ) 
	{
		cleanup();
	}
	delete mpSystem;
}

//This function will enable a selected arrow and disable the rest
void Game::arrowKeyChoice(string arrowKey)
{
	if (arrowKey == "left")
	{
		mMoveLeft = true;
		mMoveRight = false;
		mMoveUp = false;
		mMoveDown = false;
	}
	else if (arrowKey == "right")
	{
		mMoveRight = true;
		mMoveLeft = false;
		mMoveUp = false;
		mMoveDown = false;
	}
	else if (arrowKey == "up")
	{
		mMoveUp = true;
		mMoveRight = false;
		mMoveLeft = false;
		mMoveDown = false;
	}
	else if (arrowKey == "down")
	{
		mMoveDown = true;
		mMoveRight = false;
		mMoveLeft = false;
		mMoveUp = false;
	}
}


// This function gets the current instance of the static class
Game * Game::getStaticInstance() 
{
	assert( mpsGameObject != nullptr );
	return mpsGameObject;
}





// This function initializes the instance of the static class
void Game::initStaticGameInstance() 
{
	mpsGameObject = new Game(EventSystem::getStaticEventSysInstance());
}



void Game::initGameDataFile()
{
	ifstream fileIn;
	string data;
	fileIn.open("GameData.txt");//load the level 1 data text file

	while (!fileIn.eof())
	{
		fileIn >> data;

		//Load Assets
		//load the font data
		if (data == "apFont")//if the string is apFont, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mFontName = data;//assign the filepath it to the member string variable.
		}

		//load the wall/obstacle sprite data
		//load the player sprite data
		if (data == "apWallImage")
		{
			fileIn >> data;
			mWallSpriteName = data;
		}

		//load the player sprite data
		if (data == "apPlayerImage")
		{
			fileIn >> data;
			mPlayerSpriteName = data;
		}

		//load the grow powerup sprite data
		if (data == "apGrowImage")
		{
			fileIn >> data;
			mGrowSpriteName = data;
		}

		//load the bonus points powerup sprite data
		if (data == "apBonusImage")
		{
			fileIn >> data;
			mBonusSpriteName = data;
		}

		//load the slow powerup sprite data
		if (data == "apSlowImage")
		{
			fileIn >> data;
			mSlowSpriteName = data;
		}

		//load the fast powerup sprite data
		if (data == "apFastImage")
		{
			fileIn >> data;
			mFastSpriteName = data;
		}

		//load the game score data, in this case initialize it
		if (data == "hGameScore")
		{
			fileIn >> data;//take the filepath
			mGameScore = stoi(data);//assign the filepath it to the member string variable.
		}

		//load the increase score amount
		if (data == "hScoreAmt")
		{
			fileIn >> data;
			mScoreAmt = stoi(data);
		}

		//LOAD SPRITESHEET DATA
		//load sprite displacement data
		if (data == "sSpriteDisplaceX")
		{
			fileIn >> data;
			mSpriteDisplacementX = stoi(data);
		}
		if (data == "sSpriteDisplaceY")
		{
			fileIn >> data;
			mSpriteDisplacementY = stoi(data);
		}

		//load sprite sheet, sprite per row and column
		if (data == "sSpritePerRow")
		{
			fileIn >> data;
			mSpritesPerRow= stoi(data);
		}
		if (data == "sSpritePerColumn")
		{
			fileIn >> data;
			mSpritesPerColumn = stoi(data);
		}

		//Load Other data
		if (data == "oScreenDivisorCentering")
		{
			fileIn >> data;
			mScreenDivisorCentering = stoi(data);
		}
		if (data == "oBackgroundScaleVal")
		{
			fileIn >> data;
			mBackgroundScalingVal = stoi(data);
		}

		if (data == "oSpriteDimensions")
		{
			fileIn >> data;
			mSpriteDimensions.mX = stoi(data);
			fileIn >> data;
			mSpriteDimensions.mY = stoi(data);
		}
		if (data == "oUnitPos")
		{
			fileIn >> data;
			mUnitPosition.mX = stoi(data);
			fileIn >> data;
			mUnitPosition.mY = stoi(data);
		}
	}
	fileIn.close();
}

//This function will load all of the data in the file and assign it to appropriate variables.
void Game::initDataFile1()
{
	ifstream fileIn;
	string data;
	fileIn.open("Level1Data.txt");//load the level 1 data text file

	while (!fileIn.eof())
	{
		fileIn >> data;

		//Load Assets
		//load shared assets folder path
		if (data == "apAssetPath")//if the string is apAssetPath, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mAssetPath = data;//assign the filepath it to the member string variable.
		}
		//load custom assets folder path
		if (data == "apChunAssetPath")//if the string is apChunAssetPath, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mChunAssetPath = data;//assign the filepath it to the member string variable.
		}
		//load custom background data
		if (data == "apCustomBG")//if the string is apCustomBG, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mCustomBGName = data;//assign the filepath it to the member string variable.
		}

		//Load the snake data
		//load the snake speed data
		if (data == "sSpeed")//if the string is the sSpeed, s meaning Snake, then runs
		{
			fileIn >> data;//take the number that is a space away from sSpeed.
			mSnakeSpd = stoi(data);//use stoi to convert the string to an int.
		}
		//load the starting snake length data
		if (data == "sInitLength")
		{
			fileIn >> data;
			mSnakeStartLength = stoi(data);
		}

		//Load Level Specific Data
		//load the snake length requirement
		if (data == "sLengthRequired")
		{
			fileIn >> data;
			mSnakeLengthRequirement = stoi(data);
		}

		//load the walls for the first level
		if (data == "sWallPos")
		{
			fileIn >> data;//take in the first number, x
			mWallPos.mX = stoi(data);//convert the x string to an int
			fileIn >> data;//take in the second number, y
			mWallPos.mY = stoi(data);//convert the y string to an int

			mNumWalls += 1;//now add to counter, to reflect a new wall

			mpLevelManager->setLevelWallRequirements(mWallPos);//put the new position of the wall into a vector that is in the levelmanager
		}

		//load the spawn frequency
		if (data == "tFrequencyPowerUp")
		{
			fileIn >> data;
			mSpawnFrequency = stoi(data);
		}

		//load the increase score amount
		if (data == "pBonusAmt")
		{
			fileIn >> data;
			mBonusAmt = stoi(data);
		}

		//load the fast amount data
		if (data == "pFastAmt")
		{
			fileIn >> data;
			mFastAmt = stoi(data);
		}

		//load the slow amount data
		if (data == "pSlowAmt")
		{
			fileIn >> data;
			mSlowAmt = stoi(data);
		}
	}
	fileIn.close();
}

void Game::initDataFile2()
{
	ifstream fileIn;
	string data;
	fileIn.open("Level2Data.txt");//load the level 1 data text file

	while (!fileIn.eof())
	{
		fileIn >> data;

		//Load Assets
		//load shared assets folder path
		if (data == "apAssetPath")//if the string is apAssetPath, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mAssetPath = data;//assign the filepath it to the member string variable.
		}
		//load custom assets folder path
		if (data == "apChunAssetPath")//if the string is apChunAssetPath, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mChunAssetPath = data;//assign the filepath it to the member string variable.
		}
		//load custom background data
		if (data == "apCustomBG")//if the string is apCustomBG, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mCustomBGName = data;//assign the filepath it to the member string variable.
		}

		//Load the snake data
		//load the snake speed data
		if (data == "sSpeed")//if the string is the sSpeed, s meaning Snake, then runs
		{
			fileIn >> data;//take the number that is a space away from sSpeed.
			mSnakeSpd = stoi(data);//use stoi to convert the string to an int.
		}
		//load the starting snake length data
		if (data == "sInitLength")
		{
			fileIn >> data;
			mSnakeStartLength = stoi(data);
		}

		//Load Level Specific Data
		//load the snake length requirement
		if (data == "sLengthRequired")
		{
			fileIn >> data;
			mSnakeLengthRequirement = stoi(data);
		}

		//load the walls for the first level
		if (data == "sWallPos")
		{
			fileIn >> data;//take in the first number, x
			mWallPos.mX = stoi(data);//convert the x string to an int
			fileIn >> data;//take in the second number, y
			mWallPos.mY = stoi(data);//convert the y string to an int

			mNumWalls += 1;//now add to counter, to reflect a new wall

			mpLevelManager->setLevelWallRequirements(mWallPos);//put the new position of the wall into a vector that is in the levelmanager
		}

		//load the increase score amount
		if (data == "pBonusAmt")
		{
			fileIn >> data;
			mBonusAmt = stoi(data);
		}

		//load the fast amount data
		if (data == "pFastAmt")
		{
			fileIn >> data;
			mFastAmt = stoi(data);
		}

		//load the slow amount data
		if (data == "pSlowAmt")
		{
			fileIn >> data;
			mSlowAmt = stoi(data);
		}

		//load the spawn frequency
		if (data == "tFrequencyPowerUp")
		{
			fileIn >> data;
			mSpawnFrequency = stoi(data);
		}

	}
	fileIn.close();
}

void Game::initDataFile3()
{
	ifstream fileIn;
	string data;
	fileIn.open("Level3Data.txt");//load the level 1 data text file

	while (!fileIn.eof())
	{
		fileIn >> data;

		//Load Assets
		//load shared assets folder path
		if (data == "apAssetPath")//if the string is apAssetPath, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mAssetPath = data;//assign the filepath it to the member string variable.
		}
		//load custom assets folder path
		if (data == "apChunAssetPath")//if the string is apChunAssetPath, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mChunAssetPath = data;//assign the filepath it to the member string variable.
		}
		//load custom background data
		if (data == "apCustomBG")//if the string is apCustomBG, a meaning asset, p meaning path, then run
		{
			fileIn >> data;//take the filepath
			mCustomBGName = data;//assign the filepath it to the member string variable.
		}

		//Load the snake data
		//load the snake speed data
		if (data == "sSpeed")//if the string is the sSpeed, s meaning Snake, then runs
		{
			fileIn >> data;//take the number that is a space away from sSpeed.
			mSnakeSpd = stoi(data);//use stoi to convert the string to an int.
		}
		//load the starting snake length data
		if (data == "sInitLength")
		{
			fileIn >> data;
			mSnakeStartLength = stoi(data);
		}

		//Load Level Specific Data
		//load the snake length requirement
		if (data == "sLengthRequired")
		{
			fileIn >> data;
			mSnakeLengthRequirement = stoi(data);
		}

		//load the walls for the first level
		if (data == "sWallPos")
		{
			fileIn >> data;//take in the first number, x
			mWallPos.mX = stoi(data);//convert the x string to an int
			fileIn >> data;//take in the second number, y
			mWallPos.mY = stoi(data);//convert the y string to an int

			mNumWalls += 1;//now add to counter, to reflect a new wall

			mpLevelManager->setLevelWallRequirements(mWallPos);//put the new position of the wall into a vector that is in the levelmanager
		}

		//load the increase score amount
		if (data == "pBonusAmt")
		{
			fileIn >> data;
			mBonusAmt = stoi(data);
		}

		//load the fast amount data
		if (data == "pFastAmt")
		{
			fileIn >> data;
			mFastAmt = stoi(data);
		}

		//load the slow amount data
		if (data == "pSlowAmt")
		{
			fileIn >> data;
			mSlowAmt = stoi(data);
		}

		//load the spawn frequency
		if (data == "tFrequencyPowerUp")
		{
			fileIn >> data;
			mSpawnFrequency = stoi(data);
		}

	}
	fileIn.close();
}

void Game::resetMovement()
{
	mMoveRight = false;
	mMoveLeft = false;
	mMoveUp = false;
	mMoveDown = false;
}





// This function destroys the current instance of the static class
void Game::destroyStaticGameInstance() 
{
	delete mpsGameObject;
}

void Game::cleanLevel()
{
	mNumWalls = 0;
	resetMovement();//reset movement on each level. that way the snake doesn't start off  moving
	mpUnitManager->resetEating();//reset the bool that says the snake ate something

	mpUnitManager->removeAndDestroyAllUnits();//clear the previous units
	mpFoodManager->removeAndDestroyAllFruits();//clear the previous fruits
	mpWallManager->removeAndDestroyAllWalls();//clear the previous walls
	mpPowerUpManager->removeAndDestroyAllPowerUps();//clear the previous powerups
}

// This function initializes all of the allegro systems
void Game::init()
{
	//Create the managers
	mpHudManager = new HudUIManager();//creating the new hud and ui manager

	mpBufferManager = new GraphicsBufferManager();//creating the new buffer manager

	mpUnitManager = new UnitManager();//creating the new unit manager
	
	mpFoodManager = new FoodManager();//creating the new food manager

	mpLevelManager = new LevelManager(MAX_LEVELS);//creating the new level manager

	mpWallManager = new WallManager();//creating the new wall manager

	mpInputTrans = new InputTranslator(EventSystem::getStaticEventSysInstance());//creating the input translator

	// Initialize all systems
	initializeSystems();

	// Initialize Game Data
	initGameDataFile();

	// Initialize the initial data file for level one
	initDataFile1();

	mpPowerUpManager = new PowerUpManager(mSpawnFrequency);//creating the new powerup manager, done here so that way mSpawnFrequency has the info from the init datafile 1;

	//Create all buffers and add/set animations where needed

	// Create the game background image
	mpBufferManager->addBuffer(mChunAssetPath + mCustomBGName, NAME_OF_BACKGROUND_BUFFER);

	// Create the wall image
 	mpBufferManager->addBuffer(mChunAssetPath + mWallSpriteName, NAME_OF_WALL_BUFFER);

	// Create the Wall animation
	mpWallAnimation = new Animation(mpBufferManager->getBuffer(NAME_OF_WALL_BUFFER), mSpritesPerRow, mSpritesPerColumn, Vector2(DISP_WIDTH, DISP_HEIGHT), mSpriteDimensions);

	// Create Player image
	mpBufferManager->addBuffer(mChunAssetPath + mPlayerSpriteName, NAME_OF_PLAYER_SPRITE_SHEET_BUFFER);

	// Create the Player animation
	mpPlayerAnimation = new Animation(mpBufferManager->getBuffer(NAME_OF_PLAYER_SPRITE_SHEET_BUFFER), mSpritesPerRow, mSpritesPerColumn, Vector2(DISP_WIDTH, DISP_HEIGHT), mSpriteDimensions);

	// Create Grow image
	mpBufferManager->addBuffer(mChunAssetPath + mGrowSpriteName, NAME_OF_GROW_ITEM_SPRITE_SHEET_BUFFER);

	// Create the Grow animation
	mpPUGrowAnimation = new Animation(mpBufferManager->getBuffer(NAME_OF_GROW_ITEM_SPRITE_SHEET_BUFFER), mSpritesPerRow, mSpritesPerColumn, Vector2(DISP_WIDTH, DISP_HEIGHT), mSpriteDimensions);

	// Create Bonus image
	mpBufferManager->addBuffer(mChunAssetPath + mBonusSpriteName, NAME_OF_BONUS_ITEM_SPRITE_SHEET_BUFFER);

	// Create the Bonus animation
	mpPUBonusAnimation = new Animation(mpBufferManager->getBuffer(NAME_OF_BONUS_ITEM_SPRITE_SHEET_BUFFER), mSpritesPerRow, mSpritesPerColumn, Vector2(DISP_WIDTH, DISP_HEIGHT), mSpriteDimensions);

	// Create Fast Image
	mpBufferManager->addBuffer(mChunAssetPath + mFastSpriteName, NAME_OF_FAST_ITEM_SPRITE_SHEET_BUFFER);

	// Create the Fast animation
	mpPUFastAnimation = new Animation(mpBufferManager->getBuffer(NAME_OF_FAST_ITEM_SPRITE_SHEET_BUFFER), mSpritesPerRow, mSpritesPerColumn, Vector2(DISP_WIDTH, DISP_HEIGHT), mSpriteDimensions);

	// Create Slow Image
	mpBufferManager->addBuffer(mChunAssetPath + mSlowSpriteName, NAME_OF_SLOW_ITEM_SPRITE_SHEET_BUFFER);

	// Create the Slow animation
	mpPUSlowAnimation = new Animation(mpBufferManager->getBuffer(NAME_OF_SLOW_ITEM_SPRITE_SHEET_BUFFER), mSpritesPerRow, mSpritesPerColumn, Vector2(DISP_WIDTH, DISP_HEIGHT), mSpriteDimensions);

	// Create the display
	mpSystem->init( DISP_WIDTH, DISP_HEIGHT );

	//Create the fonts and color for the title screen text
	pTitleFont = new Font(mAssetPath + mFontName, 50);
	pCurrentLevelFont = new Font(mAssetPath + mFontName, 25);
	pTitleColor = new Color(1.0f, 0.0f, 1.0f, 1.0f);

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = true;
}


// This function calls system to initialize the allegro system
void Game::initializeSystems() 
{
	mpSystem->initializeSystems();
}


// This function cleans up and destroys all of the allegro systems
void Game::cleanup() 
{
	// Delete Animations
	delete mpWallAnimation;
	delete mpPlayerAnimation;
	delete mpPUGrowAnimation;
	delete mpPUBonusAnimation;
	delete mpPUSlowAnimation;
	delete mpPUFastAnimation;

	// Delete Managers
	delete mpBufferManager;
	delete mpHudManager;
	delete mpUnitManager;
	delete mpFoodManager;
	delete mpLevelManager;
	delete mpWallManager;
	delete mpPowerUpManager;

	// Delete 
	//remove the listeners
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)EXIT, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)CREATE, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)KILL, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)TOGGLE_ANIMATION, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)FLIP_ANIMATIONS, this);

	EventSystem::getStaticEventSysInstance()->removeListener((EventType)MOVE_LEFT, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)MOVE_RIGHT, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)MOVE_UP, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)MOVE_DOWN, this);

	// Delete fonts
	delete pTitleFont;
	delete pCurrentLevelFont;

	// Delete colors
	delete pTitleColor;

	// Delete Input System
	delete mpInputSys;

	// Delete Input translator
	delete mpInputTrans;

	// Delete Display
	mpSystem->cleanup();

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = false;
}





// This function executes the game loop
void Game::doLoop() 
{
	Timer gameLoop;

	
		while (!mStartGame)//run this loop and keep checking for input. If player hits enter, then the game will start and will break out of this while loop
		{
			mpHudManager->renderTitleScreen();//render title screen
			mpHudManager->flipDisplay();//flip display
			mpInputSys->updateInputStart();//Get the input/update
		}

		mStartGame = false;//this resets the ability to start the scene. That way when player reaches next scene/level they can hit a button before it goes to next stage

		while (mInGame) //run while the player hasnt died or hit the esc key.
		{
			switch (mpLevelManager->getCurrentLevel())
			{
				//Level 1
			case 1:

				mpLevelManager->setLevelSnakeRequirements(mSnakeLengthRequirement);//set the length level requirement that the snake must reach

				createContent();//create the initial snake and walls and such

				while (mpLevelManager->getCurrentLevel() == 1)
				{

					gameLoop.start(); // Start the timer

					//Check to see if the snake reaches the current levels length requirement.
					if (mpUnitManager->getSize() == mpLevelManager->getCurrentLevelLength())
					{
						mpLevelManager->nextLevel();
						gameLoop.stop();
						break;
					}

					spawnChosenPowerUp(mpPowerUpManager->randomPowerUpSpawnNumber());

					//check to see what happens to the head
					mpUnitManager->checkPositionFromBorderWalls();//this function will check the position of the units(really the head) and see if it hits the border walls
					mpUnitManager->checkPositionFromWalls(mpWallManager);//this function will check the position of the units(really the head) and see if it hits the spawned walls.

					checkSnake();//Check status of the snake

					if (mInGame == false)//then have another check to make sure that the snake is not dead, if it is stop timer and break
					{
						gameLoop.stop();
						break;
					}

					mpUnitManager->checkPositionFromFood(mpFoodManager->getTargetPos(0));
					mpUnitManager->checkPositionFromPowerUps(mpPowerUpManager);

					mpInputSys->updateInputGame();//Get the input/update

					mpUnitManager->update(MAX_TIME_BETWEEN_FRAMES); // Call update for all created units, animations
					mpFoodManager->updateFood(MAX_TIME_BETWEEN_FRAMES);// Call update for all created food,
					mpWallManager->update(MAX_TIME_BETWEEN_FRAMES);
					mpPowerUpManager->updatePowerUps(MAX_TIME_BETWEEN_FRAMES);
					mpPowerUpManager->updateSpawn((float)MAX_TIME_BETWEEN_FRAMES);

					render(); // Render all buffers in game
					mpHudManager->renderHUD();//render the hud, the level, score and fps
					mpHudManager->flipDisplay();//flip

					checkDirection();//check if which direction to move units

					gameLoop.sleepUntilElapsed(MAX_TIME_BETWEEN_FRAMES); // Sleep until enough time has elapsed

					mFPS = FRAMES_PER_SEC / gameLoop.getElapsedTime();//set the current fps to the member var double I got

					cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl; // Report elapsed time
					//cout << "SNAKE LENGTH: " << mpUnitManager->getSize() << endl; IF YOU WANT, THIS SHOWS HOW MANY SNAKE SEGMENTS/UNITS ARE THERE.
					gameLoop.stop(); // Stop the times
				}
				break;

			case 2://level 2

				cleanLevel();//clean the previous level data, to make way for new level 

				initDataFile2();//get and re initialize the member variables with content from data file 2.

				mpLevelManager->setLevelSnakeRequirements(mSnakeLengthRequirement);//pass in the required length amount

				mpPowerUpManager->setSpawnFreq(mSpawnFrequency);//set the spawn frequency to the new frequency that was gotten from datafile 2 init

				createContent();//create the initial snake and walls and such

				mStartGame = false;//this resets the ability to start the scene. That way when player reaches next scene/level they can hit a button before it goes to next stage

				while (!mStartGame)//run this loop and keep checking for input. If player hits enter, then the game will start and will break out of this while loop
				{
					mpHudManager->renderNextLevelScreen();//render next level/continue screen
					mpHudManager->flipDisplay();//flip display
					mpInputSys->updateInputGame();//Get the input/update
				}

				while (mpLevelManager->getCurrentLevel() == 2 && mInGame == true)
				{
					gameLoop.start(); // Start the timer

					//Check to see if the snake reaches the current levels length requirement.
					if (mpUnitManager->getSize() == mpLevelManager->getCurrentLevelLength())
					{
						mpLevelManager->nextLevel();
						gameLoop.stop();
						break;
					}

					spawnChosenPowerUp(mpPowerUpManager->randomPowerUpSpawnNumber());

					//check to see what happens to the head
					mpUnitManager->checkPositionFromBorderWalls();//this function will check the position of the units(really the head) and see if it hits the border walls
					mpUnitManager->checkPositionFromWalls(mpWallManager);//this function will check the position of the units(really the head) and see if it hits the spawned walls.

					checkSnake();//Check status of the snake

					if (mInGame == false)//then have another check to make sure that the snake is not dead, if it is stop timer and break
					{
						gameLoop.stop();
						break;
					}

					mpUnitManager->checkPositionFromFood(mpFoodManager->getTargetPos(0));
					mpUnitManager->checkPositionFromPowerUps(mpPowerUpManager);

					mpInputSys->updateInputGame();//Get the input/update

					mpUnitManager->update(MAX_TIME_BETWEEN_FRAMES); // Call update for all created units, animations
					mpFoodManager->updateFood(MAX_TIME_BETWEEN_FRAMES);// Call update for all created food,
					mpWallManager->update(MAX_TIME_BETWEEN_FRAMES);
					mpPowerUpManager->updatePowerUps(MAX_TIME_BETWEEN_FRAMES);
					mpPowerUpManager->updateSpawn((float)MAX_TIME_BETWEEN_FRAMES);

					render(); // Render all buffers in game
					mpHudManager->renderHUD();//render the hud, the level, score and fps
					mpHudManager->flipDisplay();//flip
		
					checkDirection();//check if which direction to move units

					gameLoop.sleepUntilElapsed(MAX_TIME_BETWEEN_FRAMES); // Sleep until enough time has elapsed

					mFPS = FRAMES_PER_SEC / gameLoop.getElapsedTime();//set the current fps to the member var double I got

					cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl; // Report elapsed time
					//cout << "SNAKE LENGTH: " << mpUnitManager->getSize() << endl; IF YOU WANT, THIS SHOWS HOW MANY SNAKE SEGMENTS/UNITS ARE THERE.
					gameLoop.stop(); // Stop the times
				}
				break;


			case 3://level 3

				cleanLevel();//clean the previous level data, to make way for new level

				initDataFile3();//get and re initialize the member variables with content from data file 3.

				mpLevelManager->setLevelSnakeRequirements(mSnakeLengthRequirement);//set the snake length requirement for this level.

				mpPowerUpManager->setSpawnFreq(mSpawnFrequency);//set the spawn frequency to the new frequency that was gotten from datafile 2 init

				createContent();//create the initial snake and walls and such

				mStartGame = false;//this resets the ability to start the scene. That way when player reaches next scene/level they can hit a button before it goes to next stage

				while (!mStartGame)//run this loop and keep checking for input. If player hits enter, then the game will start and will break out of this while loop
				{
					mpHudManager->renderNextLevelScreen();//render next level/continue screen
					mpHudManager->flipDisplay();//flip display
					mpInputSys->updateInputGame();//Get the input/update
				}

				while (mpLevelManager->getCurrentLevel() == 3 && mInGame == true)
				{
					gameLoop.start(); // Start the timer

									  //Check to see if the snake reaches the current levels length requirement.
					if (mpUnitManager->getSize() == mpLevelManager->getCurrentLevelLength())
					{
						mInGame = false;
						gameLoop.stop();
						break;
					}

					spawnChosenPowerUp(mpPowerUpManager->randomPowerUpSpawnNumber());

					//check to see what happens to the head
					mpUnitManager->checkPositionFromBorderWalls();//this function will check the position of the units(really the head) and see if it hits the border walls
					mpUnitManager->checkPositionFromWalls(mpWallManager);//this function will check the position of the units(really the head) and see if it hits the spawned walls.

					checkSnake();//Check status of the snake

					if (mInGame == false)//then have another check to make sure that the snake is not dead, if it is stop timer and break
					{
						gameLoop.stop();
						break;
					}

					mpUnitManager->checkPositionFromFood(mpFoodManager->getTargetPos(0));
					mpUnitManager->checkPositionFromPowerUps(mpPowerUpManager);

					mpInputSys->updateInputGame();//Get the input/update

					mpUnitManager->update(MAX_TIME_BETWEEN_FRAMES); // Call update for all created units, animations
					mpFoodManager->updateFood(MAX_TIME_BETWEEN_FRAMES);// Call update for all created food,
					mpWallManager->update(MAX_TIME_BETWEEN_FRAMES);// Call update for all the created wall
					mpPowerUpManager->updatePowerUps(MAX_TIME_BETWEEN_FRAMES);// Call the update that will determine when more powerups will spawn
					mpPowerUpManager->updateSpawn((float)MAX_TIME_BETWEEN_FRAMES);

					render(); // Render all buffers in game
					mpHudManager->renderHUD();//render the hud, the level, score and fps
					mpHudManager->flipDisplay();//flip

					checkDirection();//check if which direction to move units

					gameLoop.sleepUntilElapsed(MAX_TIME_BETWEEN_FRAMES); // Sleep until enough time has elapsed

					mFPS = FRAMES_PER_SEC / gameLoop.getElapsedTime();//set the current fps to the member var double I got

					cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl; // Report elapsed time
					//cout << "SNAKE LENGTH: " << mpUnitManager->getSize() << endl; IF YOU WANT, THIS SHOWS HOW MANY SNAKE SEGMENTS/UNITS ARE THERE.
					gameLoop.stop(); // Stop the times
				}
				break;
			}
		}
		mInGame = true;
		while (mInGame && mPlayAgain == false)
		{
			mpHudManager->renderEndScreen();//render end screen
			mpHudManager->flipDisplay();//flip
			mpInputSys->updateInputEnd();//get the end game input
		}
		restart();//throw the option of restarting
}

/*This function is a little of a mess, but it basically cleans the level,
*  so most of the managers are cleared and ready to take in new data
*/
void Game::restart()
{
	if (mPlayAgain == true)
	{
		mPlayAgain = false;
		cleanLevel();//clean the level
		mpLevelManager->cleanUp();//clean level manager
		initDataFile1();//init the first data file
		mStartGame = false;//reset this to false, so player can press a button before playing again
		mGameScore = 0;
		doLoop();//run the do loop
	}
}

// This function deals with the render step of the game loop
void Game::render() 
{
	// Draw the background image for the level
	mpSystem->getGraphicsSystem().drawBackground(*mpBufferManager->getBuffer(NAME_OF_BACKGROUND_BUFFER), mBackgroundScalingVal);//draw just the game background
	mpHudManager->render();//call the hud managers render that will essentialy draw the extra walls, the units, food and powerups
}

//This function uses the member variables that will be used to spawn the initial snake, the extra walls and then the starting grow fruit.
//This is to cut down on lines of code in the do loop.
void Game::createContent()
{
	mpUnitManager->spawnSnake(mSnakeStartLength, mpPlayerAnimation);//spawn the initial snake
	mpFoodManager->spawnFruit(mpPUGrowAnimation);//spawn the initial fruit
	mpWallManager->spawnWalls(mNumWalls, mpWallAnimation);//spawn the initial walls

	//set the positions of the food and walls
	mpFoodManager->setFruitPos();//set the position of fruits/food
	mpFoodManager->moveFruit();//then move them

	mpWallManager->setWallPos(mpLevelManager);//set the position of the walls
}

/*This function takes in a random number and if the powerup manager can spawn something, then use the switch*
*statement to determine which to spawn
*/
void Game::spawnChosenPowerUp(int choice)
{
	if (mpPowerUpManager->getSpawnStatus() == true)
	{
		switch (choice)
		{
		case 0:
			mpPowerUpManager->setSpawnStatus(false);
			mpPowerUpManager->spawnPowerUps("bonusPt", mpPUBonusAnimation);//spawn a type of powerup
			mpPowerUpManager->setPowerUpPos();		//set the positions of the powerups
			mpPowerUpManager->movePowerUp(mpPowerUpManager->getSize() - 1);
			break;

		case 1:
			mpPowerUpManager->setSpawnStatus(false);
			mpPowerUpManager->spawnPowerUps("slow", mpPUSlowAnimation);//spawn a type of powerup
			mpPowerUpManager->setPowerUpPos();		//set the positions of the powerups
			mpPowerUpManager->movePowerUp(mpPowerUpManager->getSize() - 1);//move them
			break;

		case 2:
			mpPowerUpManager->setSpawnStatus(false);
			mpPowerUpManager->spawnPowerUps("fast", mpPUFastAnimation);//spawn a type of powerup
			mpPowerUpManager->setPowerUpPos();		//set the positions of the powerups
			mpPowerUpManager->movePowerUp(mpPowerUpManager->getSize() - 1);//move them
			break;
		}
		
	}
}

/*This function checks the status of the snake and if its hit anything interesting,
*  it will check for bools and execute appropriate functions relating to snake and its collisions
*/
void Game::checkSnake()
{
	//check if snake is alive, like units on screen
	if (mpUnitManager->getSize() != 0)
	{
		//nothing
	}
	else
	{
 		mInGame = false;
	}
	//check to see if snake crashed/touched a barricade/wall
	if (mpUnitManager->getCrashStatus() == true)
	{
		mInGame = false;
	}
	//check to see if snake touched a grow fruit
	if (mpUnitManager->getFruitStatus() == true)//if the head has eaten a fruit run
	{
		mpUnitManager->increaseLength(mpUnitManager->getUnitPos(mpUnitManager->getSize() - 1), mpPlayerAnimation);//increase the length and have position be at old tail
		mpUnitManager->setFruitStatus(false);//reset the status so it only increases it once.
		mpFoodManager->setFruitPos();//set a new position for the fruit
		mpFoodManager->moveFruit();//move said fruit
		addScore();//add to the player score
	}

	//check to see if the snake touches a powerup
	if (mpUnitManager->getPowerUpStatus() == true)
	{
		switch (mpUnitManager->getPowerUpTypeStatus())
		{
		//bonus point powerup
		case 0:
			mpUnitManager->setPowerUpStatus(false);
			addScore(mBonusAmt);
			break;

		//speed down powerup
		case 1:
			mpUnitManager->setPowerUpStatus(false);
			deductSpeed(mSlowAmt);
			break;

		//speed up powerup
		case 2:
			mpUnitManager->setPowerUpStatus(false);
			incrementSpeed(mFastAmt);
			break;
		}
	}
}

/*This function checks which direction bool is true,
* then perform the appropriate correct movement functions
*/
void Game::checkDirection()
{
	//determine the direction of movement and call the appropriate functions.
	//pass in the snake speed and the max time between frames.
	if (mMoveLeft == true)
	{
		mpUnitManager->moveUnitsLeft(mSnakeSpd, MAX_TIME_BETWEEN_FRAMES);
	}
	if (mMoveRight == true)
	{
		mpUnitManager->moveUnitsRight(mSnakeSpd,MAX_TIME_BETWEEN_FRAMES);
	}
	if (mMoveUp == true)
	{
		mpUnitManager->moveUnitsUp(mSnakeSpd,MAX_TIME_BETWEEN_FRAMES);
	}
	if (mMoveDown == true)
	{
		mpUnitManager->moveUnitsDown(mSnakeSpd,MAX_TIME_BETWEEN_FRAMES);
	}

	//basically neutral, standby
	else if (mMoveLeft == false && mMoveRight == false
		&& mMoveUp == false && mMoveDown == false)
	{
		//nothing
	}
}

/*This handles the events that come in and then call appropriate functions
*and set appropriate booleans.*/
void Game::handleEvent(const Event & passedEvent)
{
	//Handle events for game status
	if (passedEvent.getType() == EXIT)//if the heard type is exit, then set inGame bool to false, basically ending the do lopp
	{
		mInGame = false;
	}

	if (passedEvent.getType() == START)//if the heard type is start, then set the bool to true
	{
		mStartGame = true;
	}

	if (passedEvent.getType() == RESTART)//if the heard type is restart, then allow the bool to play again, or if its already set to true, set to false
	{
		if (mPlayAgain == true)
		{
			mPlayAgain = false;
		}
		else
			mPlayAgain = true;
	}

	//Handle events for units
	if (passedEvent.getType() == CREATE)//if the heard type is create, then create a unit using the manager and add animations.
	{
		const CreateUnit& createEvent = static_cast<const CreateUnit&>(passedEvent);

		// Create a unit within the unit manager
		mpUnitManager->createUnit(createEvent.getLocation());

		// add both animations to the unit, the dean and smurf.
		mpUnitManager->addAnimation(mpUnitManager->getSize() - 1, *mpPlayerAnimation);
	}

	//The KILL, TOGGLE and FLIP animation events aren't used in this project but I did not feel it was necessary to remove them.
	if (passedEvent.getType() == KILL)//if the heard type is delete, then delete a unit
	{
		const DeleteUnit& killEvent = static_cast<const DeleteUnit&>(passedEvent);

		// Delete the unit from a point
		mpUnitManager->deleteUnitFromGivenPoint(killEvent.getLocation());
	}

	if (passedEvent.getType() == TOGGLE_ANIMATION)//if the heard type is delete, then delete a unit
	{
		// Turn on or off all units animations
		mpUnitManager->playOrStopUnitAnimations();
	}

	if (passedEvent.getType() == FLIP_ANIMATIONS)//if the heard type is delete, then delete a unit
	{
		// Flip the animation of the last unit
		mpUnitManager->swapAnimations(mpUnitManager->getSize() - 1);
	}

	//Handle events for moving units, these allow the game to know which arrow key is pressed, and then do the checkDirection function.
	if (passedEvent.getType() == MOVE_LEFT)
	{
		arrowKeyChoice("left");
	}
	if (passedEvent.getType() == MOVE_RIGHT)
	{
		arrowKeyChoice("right");
	}
	if (passedEvent.getType() == MOVE_UP)
	{
		arrowKeyChoice("up");
	}
	if (passedEvent.getType() == MOVE_DOWN)
	{
		arrowKeyChoice("down");
	}
}