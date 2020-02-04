#include "Game.h"
#include "Unit.h"
#include "Animation.h"

Game * Game::mpGameObject = nullptr;

// This function is the default constructor for this class
Game::Game()
{
	// Create the system object
	mCurrentSystem = new System();
}





// This function is the destructor for this class
Game::~Game()
{
	if ( mIsDisplaying ) 
	{
		cleanup();
	}
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
	mpGameObject = new Game;
}





// This function destroys the current instance of the static class
void Game::destroyStaticInstance() 
{
	delete mpGameObject;
}





// This function initializes all of the allegro systems
void Game::init()
{
	mUnitManager = new UnitManager();

	// Initialize all systems
	initializeSystems();

	// Create the forest backgroud image
	mBufferManager.addBuffer(ASSET_PATH + FOREST_FILENAME, NAME_OF_FOREST_BUFFER);

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

	// Delete Unit Manager
	delete mUnitManager;

	// Delete Display
	mCurrentSystem->cleanup();

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = false;
}





// This function executes the game loop
void Game::doLoop() 
{
	bool inGame = true;
	Timer gameLoop;


	while ( inGame ) 
	{
		gameLoop.start(); // Start the timer

		// Get Input
		mMouseInput = mCurrentSystem->getMouseState();
		mKeyboardInput = mCurrentSystem->getKeyState();

		// The following code checks if escape has been pressed. 
		// If it has, then exit the game
		if ( mKeyboardInput == KEY_ESCAPE ) 
		{
			inGame = false;
		}

		// The following code checks if escape has been pressed. 
		// If it has, then switch animations of the units
		if ( mKeyboardInput == KEY_ENTER )
		{
			mUnitManager->swapAnimations(mUnitManager->getSize() - 1);
		}

		// The following code checks if the left mouse button has been pressed, 
		// create a unit at the mouse position
		if ( mMouseInput == MOUSE_LEFT )
		{
			// Create a unit within the unit manager
			mUnitManager->createUnit(mCurrentSystem->getMousePosition());

			// Add the dean smurf walk animation and the default smurf walk animation to the newly created smurf unit
			mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mSmurfWalkAnimation);
			mUnitManager->addAnimation(mUnitManager->getSize() - 1, *mDeanSmurfWalkAnimation);
		}

		// The following code checks if the right mouse button has been pressed, 
		// and a unit is in the relative position of the mouse position, delete the unit
		if ( mMouseInput == MOUSE_RIGHT ) 
		{
			mUnitManager->deleteUnitFromGivenPoint(mCurrentSystem->getMousePosition());
		}

		// The following code checks if space has been pressed, 
		// pause animations for all created units
		if ( mKeyboardInput == KEY_SPACE ) 
		{
			mUnitManager->playOrStopUnitAnimations();
		}

		mUnitManager->update( MAX_TIME_BETWEEN_FRAMES ); // Call update for all created units
		
		render(); // Render all buffers in game

		gameLoop.sleepUntilElapsed( MAX_TIME_BETWEEN_FRAMES ); // Sleep until enough time has elapsed

		cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl; // Report elapsed time

		gameLoop.stop(); // Stop the times

	}	
}





// This function deals with the render step of the game loop
void Game::render() 
{
	// Draw the background image for the level
	mCurrentSystem->getGraphicsSystem().drawBackground( *mBufferManager.getBuffer(NAME_OF_FOREST_BUFFER), BACKGROUND_SCALING_VALUE );

	// Draw all units onto the back buffer
	mUnitManager->draw();

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