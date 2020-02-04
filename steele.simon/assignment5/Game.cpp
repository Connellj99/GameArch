#include "Game.h"
#include "Unit.h"
#include "Animation.h"

Game * Game::mpGameObject = nullptr;

// This function is the default constructor for this class
Game::Game(EventSystem* pEventSystem)
	:EventListener(pEventSystem)
{

	// Listen to all events that need to be listened for
	pEventSystem->addListener((EventType)SWITCH_ANIMATIONS, this);
	pEventSystem->addListener((EventType)QUIT_GAME, this);
	pEventSystem->addListener((EventType)STOP_START_ANIMATION, this);
	pEventSystem->addListener((EventType)CREATE_UNITS, this);
	pEventSystem->addListener((EventType)DELETE_UNITS, this);

	// Create the system object
	mCurrentSystem = new System();

	// Create the input system object
	mCurrentInputSystem = new InputSystem();
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

	// Create the forest backgroud image
	mBufferManager.addBuffer(ASSET_PATH + FOREST_FILENAME, NAME_OF_FOREST_BUFFER);
	addBackgroundImage( mBufferManager.getBuffer(NAME_OF_FOREST_BUFFER) );

	// Create the regular smurf animation
	mBufferManager.addBuffer(ASSET_PATH + SMURF_SPRITE_FILENAME, NAME_OF_SMURF_SPRITE_SHEET_BUFFER );
	mSmurfWalkAnimation = new Animation( mBufferManager.getBuffer( NAME_OF_SMURF_SPRITE_SHEET_BUFFER ), SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2( DISP_WIDTH, DISP_HEIGHT ), SMURF_DIMENSIONS );

	// Create the dean smurf animation
	mBufferManager.addBuffer( ASSET_PATH + DEAN_SPRITE_FILENAME, NAME_OF_DEAN_SMURF_SPRITE_SHEET_BUFFER );
	mDeanSmurfWalkAnimation = new Animation( mBufferManager.getBuffer( NAME_OF_DEAN_SMURF_SPRITE_SHEET_BUFFER ), SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2( DISP_WIDTH, DISP_HEIGHT ), SMURF_DIMENSIONS );

	// Create the display
	mCurrentSystem->init( DISP_WIDTH, DISP_HEIGHT );

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = true;
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
	delete mDeanSmurfWalkAnimation;
	delete mSmurfWalkAnimation;
	delete mTranslator;

	// Delete Unit Manager
	delete mUnitManager;

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
	mInGame = true;
	Timer gameLoop;


	while ( mInGame ) 
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
		cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl;

		// Stop the timer
		gameLoop.stop();

	}	
}





// This function deals with the render step of the game loop
void Game::render() 
{
	// Draw the background image for the level
	mCurrentSystem->getGraphicsSystem().drawBackground( *mBackgroundImage, BACKGROUND_SCALING_VALUE );

	// Draw all units onto the back buffer
	mUnitManager->draw();

	// Flip display after everything has been drawn to the back buffer
	flipDisplay();
}





// This function creates a background image based 
// on a sprite given by the user
void Game::addBackgroundImage( GraphicsBuffer * newBackground ) 
{
	mBackgroundImage = newBackground;
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

	if (theEvent.getType() == SWITCH_ANIMATIONS) 
	{
		// Swap the animation of the most recently created unit
		mUnitManager->swapAnimations(mUnitManager->getSize() - 1);
	}

	if (theEvent.getType() == QUIT_GAME) 
	{
		// Get out of the game loop
		mInGame = false;
	}

	if (theEvent.getType() == STOP_START_ANIMATION) 
	{
		// Stop or start all current units' animations
		mUnitManager->playOrStopUnitAnimations();
	}

	if (theEvent.getType() == CREATE_UNITS) 
	{
		// Create a new version of the place unit event rathered from the passed in value
		const PlaceUnitEvent& placeEvent = static_cast<const PlaceUnitEvent&>(theEvent);

		// Create a unit within the unit manager
		mUnitManager->createUnit(placeEvent.getLocation());

		// Add the dean smurf walk animation and the default smurf walk animation to the newly created smurf unit
		mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mSmurfWalkAnimation);
		mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mDeanSmurfWalkAnimation);
	}

	if (theEvent.getType() == DELETE_UNITS) 
	{
		// Create a new version of the destroy unit event rathered from the passed in value
		const DestroyUnitEvent& destroyEvent = static_cast<const DestroyUnitEvent&>(theEvent);

		// Delete all units within the given mouse clicking radius
		mUnitManager->deleteUnitFromGivenPoint(destroyEvent.getLocation());
	}
}