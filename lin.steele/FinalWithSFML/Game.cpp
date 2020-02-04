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
	pEventSystem->addListener((EventType)MAKE_PLAYER_JUMP, this);
	pEventSystem->addListener((EventType)MOVE_PLAYER_RIGHT, this);
	pEventSystem->addListener((EventType)MOVE_PLAYER_LEFT, this);

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

	// Create a unit within the unit manager
	mUnitManager->createPlayer(Vector2(300, 300));

	// Add the dean smurf walk animation and the default smurf walk animation to the newly created smurf unit
	mUnitManager->addPlayerAnimation(*mPlayerAnimation);

	// Create the Floor
	createBlocks(BLOCKS_PER_FLOOR);

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = true;
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

	// Delete Animations
	delete mPlayerAnimation;
	delete mDefaultBlockAnimation;
	delete mBrickBlockAnimation;
	delete mQuestionBlockAnimation;
	delete mQuestionBlockEmptyAnimation;

	// Delete the Game font

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

	}

	if (theEvent.getType() == QUIT_GAME) 
	{
		mInApplication = false;
	}

	if (theEvent.getType() == MAKE_PLAYER_JUMP) 
	{
		mUnitManager->getPlayer()->jump();
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
	}

	if (theEvent.getType() == MOVE_PLAYER_LEFT) 
	{
		mUnitManager->getPlayer()->movePlayerLeft();
	}

	if (theEvent.getType() == MOVE_PLAYER_RIGHT)
	{
		mUnitManager->getPlayer()->movePlayerRight();
	}
}





// This function gets the current Unit Manager
UnitManager * Game::getUnitManager() 
{
	return mUnitManager;
}





// This function returns the display dimensions for the game
Vector2 Game::getDisplayDimensions() 
{
	return mDisplayDimensions;
}





// This function changes and displays the FPS by a certain amount
void Game::changeFPS(double newFPS) 
{
	mFramesPerSecond = newFPS;
}





// This function gets the current state of the game
bool Game::getStateOfGame() 
{
	return mInGame;
}





// This function creates the entire floor of the level
void Game::createBlocks(int amountOfBlocks) 
{
	mUnitManager->createUnit(Vector2(0, mDisplayDimensions.mY - mDefaultBlockDimensions.mY));
	mUnitManager->addAnimation(0, *mDefaultBlockAnimation);

	for (int i = 1; i < amountOfBlocks; i++) 
	{
		mUnitManager->createUnit(Vector2(mDefaultBlockDimensions.mX * i, mDisplayDimensions.mY - mDefaultBlockDimensions.mY));
		mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mDefaultBlockAnimation);
	}

	mUnitManager->createBrickBlock(Vector2(200, 400));
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mBrickBlockAnimation);

	mUnitManager->createQuestionBlock(Vector2(232, 200));
	mUnitManager->getUnit(mUnitManager->getSize() - 1)->setUnitType(QUESTION_BLOCK);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mQuestionBlockAnimation);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mQuestionBlockEmptyAnimation);

	mUnitManager->createQuestionBlock(Vector2(mDefaultBlockDimensions.mX  * 10, mDisplayDimensions.mY - (mDefaultBlockDimensions.mY * 5)));
	mUnitManager->getUnit(mUnitManager->getSize() - 1)->setUnitType(QUESTION_BLOCK);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mQuestionBlockAnimation);
	mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mQuestionBlockEmptyAnimation);
}





// This function gets the boundaries the player can move through
Vector2 Game::getPlayerBounds()
{
	return mPlayerDimensions;
}