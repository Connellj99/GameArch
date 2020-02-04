#include "Game.h"
#include "Unit.h"
#include "Animation.h"

Game * gpGameObject = NULL;


// This function is the default constructor for this class
Game::Game()
{
	// Create the system object
	mCurrentSystem = new System();

	mAllUnits = vector<Unit>();
}





// This constructor takes in the time between each frame,
// which is inputted by the user
Game::Game(double newTimeBetweenFrames)
{
	// Create the system object
	mCurrentSystem = new System();

	mAllUnits = vector<Unit>();
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





// This function initializes all of the allegro systems
void Game::init()
{
	// Initialize all systems
	initializeSystems();

	// Create the forest backgroud image
	mForestImage = new GraphicsBuffer( ASSET_PATH + FOREST_FILENAME );
	mForest = new Sprite( mForestImage, 0, 0, false, Vector2( DISP_WIDTH, DISP_HEIGHT ) );
	addBackgroundImage( *mForest );

	// Create the regular smurf animation
	mSmurfSpriteSheet = new GraphicsBuffer( ASSET_PATH + SMURF_SPRITE_FILENAME );
	mSmurfSprites = new Sprite( mSmurfSpriteSheet, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_X, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_Y, false, SMURF_DIMENSIONS );
	mSmurfWalkAnimation = new Animation( *mSmurfSprites, SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2( DISP_WIDTH, DISP_HEIGHT ), SMURF_DIMENSIONS );

	// Create the dean smurf animation
	mDeanSpriteSheet = new GraphicsBuffer( ASSET_PATH + DEAN_SPRITE_FILENAME );
	mDeanSmurfSprites = new Sprite( mDeanSpriteSheet, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_X, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_Y, false, SMURF_DIMENSIONS );
	mDeanSmurfWalkAnimation = new Animation( *mDeanSmurfSprites, SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2( DISP_WIDTH, DISP_HEIGHT ), SMURF_DIMENSIONS );

	// Create the smurf unit
	mSmurf = new Unit();

	// Add all animations to the smurf unit
	mSmurf->setAnimation( mSmurfWalkAnimation );
	mSmurf->setAnimation( mDeanSmurfWalkAnimation );

	// Center smurf unit to screen
	centerToScreen( *mSmurf );

	// add unit to the game
	addUnit( *mSmurf );

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
	// Delete Forest-related buffers
	delete mForestImage;
	delete mForest;

	// Delete Dean Smurf-related buffers
	delete mDeanSpriteSheet;
	delete mDeanSmurfSprites;

	// Delete Smurf-related buffers
	delete mSmurfSpriteSheet;
	delete mSmurfSprites;

	// Delete Animations
	delete mDeanSmurfWalkAnimation;
	delete mSmurfWalkAnimation;

	// Delete Units
	delete mSmurf;

	// Delete Display
	mCurrentSystem->cleanup();

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = false;
}





// This function executes the game loop
void Game::DoLoop() 
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
		if ( mKeyboardInput == key_escape ) 
		{
			inGame = false;
		}

		// The following code checks if escape has been pressed. 
		// If it has, then switch animations of the units
		if ( mKeyboardInput == key_enter )
		{
			for (int i = 0, max = mAllUnits.size(); i < max; i++) 
			{
				mAllUnits[i].swapAnimation();
			}
		}

		// The following code checks if escape has been pressed. 
		// If it has and a certain unit is visible, move the unit to the mouse position
		if ( mMouseInput == mouse_left )
		{
			for (int i = 0, max = mAllUnits.size(); i < max; i++)
			{
				if (mAllUnits[i].isVisible())
				{
					mAllUnits[i].moveToMousePosition(mCurrentSystem->getMousePosition());
				}
			}
		}

		// The following code checks if escape has been pressed. 
		// If it has, then speed up animation
		if ( mKeyboardInput == key_f ) 
		{
			for (int i = 0, max = mAllUnits.size(); i < max; i++)
			{
				mAllUnits[i].changeAnimationSpeeds( -SMURF_WALK_SPEED_MODIFICATION_VALUE );
			}
		}

		// The following code checks if escape has been pressed. 
		// If it has, then slow down animation
		if ( mKeyboardInput == key_s ) 
		{
			for (int i = 0, max = mAllUnits.size(); i < max; i++)
			{
				mAllUnits[i].changeAnimationSpeeds( SMURF_WALK_SPEED_MODIFICATION_VALUE );
			}
		}


		// The following code updates all of the units
		for (int i = 0, max = mAllUnits.size(); i < max; i++)
		{
			mAllUnits[i].update( MAX_TIME_BETWEEN_FRAMES );
		}

		render(); // Render all buffers in game

		gameLoop.sleepUntilElapsed( MAX_TIME_BETWEEN_FRAMES ); // Sleep until enough time has elapsed

		cout << "Time per each frame: " << gameLoop.getElapsedTime() << " ms" << endl; // Report elapsed time

		gameLoop.stop(); // Stop the times

	}	
}





// This function deals with the render step of the game loop
void Game::render() 
{
	mCurrentSystem->getGraphicsSystem().draw( mBackgroundImage.getLoc(), mBackgroundImage, BACKGROUND_SCALING_VALUE ); // Draw the background image for the level

	// The following code draws an image to the back buffer 
	// based on where the sprites are located
	for (int i = 0, max = mAllUnits.size(); i < max; i++)
	{
		mAllUnits[i].draw();
	}

	flipDisplay(); // Flip display after everything has been drawn to the back buffer
}





// This funcion adds a unit to the units update vector
void Game::addUnit( Unit newUnit ) 
{
	mAllUnits.push_back( newUnit );
}





// This function creates a background image based 
// on a sprite given by the user
void Game::addBackgroundImage( Sprite& newBackground ) 
{
	mBackgroundImage = newBackground;
}





// This function flips the current display to go
// to the next frame
void Game::flipDisplay() 
{
	mCurrentSystem->flipDisplay();
}





// This function takes a given unit and centers it to the screen
void Game::centerToScreen( Unit& unitToBeCentered ) 
{
	Vector2 centerOfScreen = Vector2( double(DISP_WIDTH) / SCREEN_DIVISOR_FOR_CENTERING, double(DISP_HEIGHT) / SCREEN_DIVISOR_FOR_CENTERING );
	unitToBeCentered.moveToMousePosition( centerOfScreen );
}





// This function gets the current system
System * Game::getCurrentSystem() 
{
	return mCurrentSystem;
}