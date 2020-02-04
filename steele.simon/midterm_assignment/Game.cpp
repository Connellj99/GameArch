#include "Game.h"
#include "Unit.h"
#include "Animation.h"

Game * Game::mpGameObject = nullptr;

// This function is the default constructor for this class
Game::Game(EventSystem* pEventSystem)
	:EventListener(pEventSystem)
{

	// Listen to all events that need to be listened for
	pEventSystem->addListener((EventType)QUIT_GAME, this);
	pEventSystem->addListener((EventType)MOVE_PLAYER, this);
	pEventSystem->addListener((EventType)SHOOT_BULLET, this);
	pEventSystem->addListener((EventType)START_GAME, this);

	// Set the score to zero and number of time an extra life rewarded to one
	mScore = 0;
	mNumberOfTimeExtraLifeRewarded = 1;

	// Set Frames per second to zero
	mFramesPerSecond = 0;

	// Create the system object
	mCurrentSystem = new System();

	// Create the input system object
	mCurrentInputSystem = new InputSystem();

	// Set in-game to false
	mInGame = false;
}





// This function is the destructor for this class
Game::~Game()
{
	if ( mIsDisplaying ) 
	{
		cleanup();
	}

	delete mCurrentInputSystem;
	delete mCurrentSystem;
}





// This function gets the current instance of the static class
Game * Game::getStaticInstance() 
{
	assert( mpGameObject != nullptr );
	return mpGameObject;
}





// This function initializes the instance of the static class
void Game::initStaticInstance() 
{
	mpGameObject = new Game(EventSystem::getStaticInstance());
}





// This function destroys the current instance of the static class
void Game::destroyStaticInstance() 
{
	delete mpGameObject;
}





// This function initializes all of the allegro systems
void Game::init()
{

	// Create the new unit manager
	mUnitManager = new UnitManager();

	// Create the new input translator
	mTranslator = new InputTranslator(EventSystem::getStaticInstance());

	// Initialize all systems
	initializeSystems();
	mCurrentInputSystem->init();

	// Create the Text Manager
	mTextManager = new TextManager();

	// Read the Game values text file
	mReader.readFile(TEXT_FILE_PATH);

	// Create window and initialize all systems
	mCurrentSystem->init(mDisplayDimensions.mX, mDisplayDimensions.mY);

	// Create the forest backgroud image
	addBackgroundImage(mBufferManager.getBuffer(NAME_OF_BACKGROUND_BUFFER));

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = true;

	// Set the Introductory text to active
	mTextManager->getText(NAME_OF_INTRO_TEXT)->setTextToActive();
	mTextManager->getText(NAME_OF_INSTRUCT_TEXT)->setTextToActive();

	mNumOfWaves = 1;
	mPlayerLives = mPlayerInitialLives;
}




// This function creates a background image based 
// on a sprite given by the user
void Game::addBackgroundImage(GraphicsBuffer * newBackground)
{
	mBackgroundImage = newBackground;
}





// This function calls system to initialize the allegro system
void Game::initializeSystems() 
{
	mCurrentSystem->initializeSystems();
}





// This function cleans up and destroys all of the allegro systems
void Game::cleanup() 
{
	// If yes, delete Animations
	delete mCentipedeSegmentAnimation;
	delete mCentipedeHeadAnimation;
	delete mPlayerAnimation;
	delete mBulletAnimation;
	delete mMushroomOneAnimation;
	delete mMushroomTwoAnimation;
	delete mMushroomThreeAnimation;
	delete mMushroomFourAnimation;

	// Delete the Game font
	delete mGameFont;

	// Delete Game Texts
	delete mTextManager;

	// Delete Unit Manager
	delete mUnitManager;

	// Delete the Input Translator
	delete mTranslator;

	// Cleanup input system
	mCurrentInputSystem->cleanup();

	// Delete Display
	mCurrentSystem->cleanup();

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = false;
}





// This function executes the game loop
void Game::doLoop() 
{
	mInApplication = true;
	Timer gameLoop;

	while ( mInApplication ) 
	{
		// Start the timer
		gameLoop.start();

		// Get Input
		mCurrentInputSystem->update();

		// Call update for all created units
		mUnitManager->update( MAX_TIME_BETWEEN_FRAMES );
		
		// Render all buffers in game
		render();

		// Sleep until enough time has elapsed
		gameLoop.sleepUntilElapsed( MAX_TIME_BETWEEN_FRAMES );

		// Report elapsed time
		changeFPS(FRAMES_PER_SECOND_DIVISOR / gameLoop.getElapsedTime());
		cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl;

		// Stop the timer
		gameLoop.stop();

	}	
}





// This function deals with the render step of the game loop
void Game::render() 
{
	// Draw the background image for the level
	mCurrentSystem->getGraphicsSystem().drawBackground(*mBackgroundImage, mBackgroundScalingValue);

	// Draw all units onto the back buffer
	mUnitManager->draw();

	// Draw all active texts
	mTextManager->draw();

	// Flip display after everything has been drawn to the back buffer
	flipDisplay();
}





// This function flips the current display to go
// to the next frame
void Game::flipDisplay() 
{
	mCurrentSystem->flipDisplay();
}





// This function gets the current system
System * Game::getCurrentSystem() 
{
	return mCurrentSystem;
}





// This function handles an event whenever the lister 
// (this object) recieves an event its listening for
void Game::handleEvent(const Event &theEvent) 
{

	if (theEvent.getType() == START_GAME && mInGame == false) 
	{
		if (mPlayerLives == 0) 
		{
			restartGame();
		}
		else 
		{
			startGame();
		}
	}

	if (theEvent.getType() == QUIT_GAME) 
	{
		// Get out of the game loop
		endApplication();
	}

	if (theEvent.getType() == MOVE_PLAYER && mInGame) 
	{
		// Create a new version of the destroy unit event rathered from the passed in value
		const MovePlayerEvent& moveEvent = static_cast<const MovePlayerEvent&>(theEvent);

		// Move the player to that specific location
		mUnitManager->movePlayer(moveEvent.getLocation());
	}

	if (theEvent.getType() == SHOOT_BULLET && mInGame) 
	{
		shootBullet();
	}
}





// This function shoots a bullet at the position of the player
void Game::shootBullet() 
{
	// Create a bullet centered in the middle of the player object
	Vector2 newPos = Vector2(mUnitManager->getPlayer()->getLocation().mX, mUnitManager->getPlayer()->getLocation().mY);
	mUnitManager->createBullet(newPos);

	// Add the bullet animation to the newly created bullet
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mBulletAnimation);
}





// This fuction spawns all of the mushroom specified within the game
void Game::spawnMushrooms() 
{
	int newX, 
		newY;

	// Make sure all random positions are truly random 
	srand(time(NULL));

	for (int i = 0; i < mMushroomsPerLevel; i++) 
	{
		// Pick a random spot outside of the player's
		// moving box and the width of the display
		newX = rand() % mDisplayDimensions.mX;
		newY = rand() % mPlayerBounds.mY;

		// Align the new values to the grid of Mushrooms
		newX -= newX % mMushroomDimensions.mX;
		newY -= newY % mMushroomDimensions.mY;

		// Is the spawned Mushroom on the top row?
		if (newY == 0) 
		{
			// If yes, move it one row down
			newY = mMushroomDimensions.mY;
		}

		// Create a Mushroom at the random position
		createMushroom(Vector2(newX, newY));
	}
}





// This function creates a Mushroom Gameobject and assigns all of the animations
// asocciated with each health level for the Mushroom
void Game::createMushroom(Vector2 newPos) 
{
	mUnitManager->createMushroom(Vector2(newPos.mX, newPos.mY));

	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mMushroomOneAnimation);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mMushroomTwoAnimation);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mMushroomThreeAnimation);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mMushroomFourAnimation);
}





// This function gets the current Unit Manager
UnitManager * Game::getUnitManager() 
{
	return mUnitManager;
}





// This function ends the level by breaking out of the game loop by
// setting mInGame to false
void Game::endApplication() 
{
	mInApplication = false;
}





// This function adds to the current game score by a given amount
void Game::addToScore(int scoreToBeAdded) 
{
	mScore += scoreToBeAdded;

	// Is the score the minimum for an extra life
	if (mScore >= mExtraLifeMinimumScore * mNumberOfTimeExtraLifeRewarded ) 
	{
		// If yes, then add a life and display it
		mNumberOfTimeExtraLifeRewarded++;
		mPlayerLives += 1;
		mTextManager->getText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT)->changeMessage(mLivesRemainingDisplayTextMessage + to_string(mPlayerLives));
	}

	mTextManager->getText(NAME_OF_SCORE_TEXT)->changeMessage(mScoreTextMessage + to_string(mScore));
}





// This function starts the game and creates the units
void Game::startGame() 
{
	// Reset the remaining amount of segments
	mNumOfSegmentsRemaining = mNumOfSegments;

	// Create a unit within the unit manager
	mUnitManager->createPlayer(Vector2(400, 600));

	// Add the dean smurf walk animation and the default smurf walk animation to the newly created smurf unit
	mUnitManager->addPlayerAnimation(*mPlayerAnimation);

	// Spawn all of the Mushrooms inside of the game
	spawnMushrooms();

	// Create the Centipede and assign the proper animations to it
	mUnitManager->createCentipede(mInitialCentipedePosition, mNumOfSegments);
	mUnitManager->getCentipede(mUnitManager->getCentipedeVectorSize() - 1)->addAnimation(*Game::getStaticInstance()->mCentipedeSegmentAnimation);
	mUnitManager->getCentipede(mUnitManager->getCentipedeVectorSize() - 1)->addAnimation(*Game::getStaticInstance()->mCentipedeHeadAnimation);


	// Set the introductory text to inactive
	mTextManager->getText(NAME_OF_INTRO_TEXT)->setTextToInactive();
	mTextManager->getText(NAME_OF_INSTRUCT_TEXT)->setTextToInactive();

	// Set the score text to active and display the score
	mTextManager->getText(NAME_OF_SCORE_TEXT)->setTextToActive();
	mTextManager->getText(NAME_OF_SCORE_TEXT)->changeMessage(mScoreTextMessage + to_string(mScore));

	// Set the lives remaining text to active
	mTextManager->getText(NAME_OF_LIVES_REMAINING_TEXT)->setTextToActive();
	mTextManager->getText(NAME_OF_LIVES_REMAINING_TEXT)->changeMessage(mLivesRemainingTextMessage + to_string(mPlayerLives));

	// Set the FPS to active and display the frames per second
	mTextManager->getText(NAME_OF_FPS_TEXT)->setTextToActive();
	mTextManager->getText(NAME_OF_FPS_TEXT)->changeMessage(to_string(mFramesPerSecond));

	// Disable the lives remaining text
	mTextManager->getText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT)->setTextToInactive();

	// Set the game to active
	mInGame = true;
}





// This function deducts the number of segments remaining in the game
void Game::deductNumOfSegments() 
{
	mNumOfSegmentsRemaining -= 1;
	if (mNumOfSegmentsRemaining == 0) 
	{
		getUnitManager()->createCentipede(mInitialCentipedePosition, mNumOfSegments);
		mUnitManager->getCentipede(mUnitManager->getCentipedeVectorSize() - 1)->addAnimation(*Game::getStaticInstance()->mCentipedeSegmentAnimation);
		mUnitManager->getCentipede(mUnitManager->getCentipedeVectorSize() - 1)->addAnimation(*Game::getStaticInstance()->mCentipedeHeadAnimation);

		mNumOfSegmentsRemaining = mNumOfSegments;
		mNumOfWaves++;
	}
}





// This function gets the current Centipede speed
double Game::getCentipedeSpeed() 
{
	// Calculate the speed
	double speed = (mInitialSpeedOfCentipede - (mNumOfWaves * mNumOfWaves)) - (mNumOfSegments - mNumOfSegmentsRemaining);

	// Is the speed is less than  or equal to one?
	if (speed <= 1) 
	{
		// If yes, then set the speed from one
		speed = 1;
	}

	return speed;
}





// This function ends the specific iteration of the game
void Game::endLife() 
{
	// Remove all Units from the screen
	mUnitManager->removeAllUnits();
	mInGame = false;
	mPlayerLives--;

	// Set score Text to inactive
	mTextManager->getText(NAME_OF_SCORE_TEXT)->setTextToInactive();

	// Set remaining lives text to inactive
	mTextManager->getText(NAME_OF_LIVES_REMAINING_TEXT)->setTextToInactive();

	// Set FPS Text to inactive
	mTextManager->getText(NAME_OF_FPS_TEXT)->setTextToInactive();

	// Are There any lives remaining?
	if (mPlayerLives == 0) 
	{
		// If no, then end the application
		endGame();
	}
	else 
	{
		// If yes, then enable the lives remaining text
		mTextManager->getText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT)->changeMessage(mLivesRemainingDisplayTextMessage + to_string(mPlayerLives));
		mTextManager->getText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT)->setTextToActive();
	}
}





// This function creates a game over screen and gives the player the option to start over
void Game::endGame() 
{
	mTextManager->getText(NAME_OF_END_TEXT)->setTextToActive();
}





// This function restarts the game and resets all in-game values
void Game::restartGame() 
{
	mNumOfWaves = 1;
	mScore = 0;
	mPlayerLives = mPlayerInitialLives;
	mTextManager->getText(NAME_OF_END_TEXT)->setTextToInactive();
	startGame();
}





// This function gets the boundaries the player can move through
Vector2 Game::getBoundsOfPlayer() 
{
	return mPlayerBounds;
}





// This function gets what the initial health of the mushroom should be
int Game::getInitialHealthOfMushroom() 
{
	return mInitialHealthOfAMushroom;
}





// This function gets the scoring value for a Centipede segment
int Game::getScoringValueForCentipedeSegment() 
{
	return mCentipedeScoringValue;
}





// This function gets the speed for the bullet
int Game::getBulletSpeed() 
{
	return mBulletSpeed;
}





// This function returns the display dimensions for the game
Vector2 Game::getDisplayDimensions() 
{
	return mDisplayDimensions;
}





// This function gets the sprite dimensions of the Mushroom
Vector2 Game::getMushroomDimensions() 
{
	return mMushroomDimensions;
}





// This function gets the dimensions of the centipede sprites
Vector2 Game::getCentipedeDimensions() 
{
	return mCentipedeDimensions;
}





// This function changes and displays the FPS by a certain amount
void Game::changeFPS(double newFPS) 
{
	mFramesPerSecond = newFPS;
	mTextManager->getText(NAME_OF_FPS_TEXT)->changeMessage(mFPSTextMessage + to_string(mFramesPerSecond));
}





// This function gets the current state of the game
bool Game::getStateOfGame() 
{
	return mInGame;
}