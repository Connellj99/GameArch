#include "Game.h"
#include "Unit.h"
#include "Animation.h"

#include "GraphicsBufferManager.h"

#include "UnitManager.h"

Game* Game::mpGameInstance = nullptr;

// This function is the default constructor for this class
Game::Game()
{
	// Create the system object
	mpCurrentSystem = new System();

	mAllUnits = vector<Unit>();
}





// This constructor takes in the time between each frame,
// which is inputted by the user
Game::Game(double newTimeBetweenFrames)
{
	// Create the system object
	mpCurrentSystem = new System();

	mAllUnits = vector<Unit>();
}





// This function is the destructor for this class
Game::~Game()
{
	if ( mIsDisplaying ) 
	{
		cleanup();
	}
	delete mpCurrentSystem;
}





// This function initializes all of the allegro systems
void Game::init()
{
	// Initialize all systems
	initializeSystems();

	mpGraphicsBufferManagement = new GraphicsBufferManager;//create the new graphic buffer manager

	mpUnitManagement = new UnitManager;//create the new unit manager

	mpGraphicsBufferManagement->addBuffer(new GraphicsBuffer(800,600));//create a new graphics buffer that will serve as the empty canvas sort of speaking

	// Create the forest backgroud image
	mpForestImage = new GraphicsBuffer( ASSET_PATH + FOREST_FILENAME );
	mpGraphicsBufferManagement->addBuffer(mpForestImage);//add the forest buffer to the buffer manager.

	mpForest = new Sprite( mpForestImage, 0, 0, false, Vector2( DISP_WIDTH, DISP_HEIGHT ) );
	addBackgroundImage( *mpForest );

	// Create the regular smurf animation
	mpSmurfSpriteSheet = new GraphicsBuffer( ASSET_PATH + SMURF_SPRITE_FILENAME );
	
	mpGraphicsBufferManagement->addBuffer(mpSmurfSpriteSheet);//add the smurf buffer to the buffer manager

	mpSmurfSprites = new Sprite( mpSmurfSpriteSheet, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_X, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_Y, false, SMURF_DIMENSIONS );
	mpSmurfWalkAnimation = new Animation(*mpSmurfSprites, /*mGraphicsBufferManagement->getBuffer(2), mGraphicsBufferManagement,*/SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2(DISP_WIDTH, DISP_HEIGHT), SMURF_DIMENSIONS);

	// Create the dean smurf animation
	mpDeanSpriteSheet = new GraphicsBuffer( ASSET_PATH + DEAN_SPRITE_FILENAME );

	mpGraphicsBufferManagement->addBuffer(mpDeanSpriteSheet);//add the dean buffer to the buffer manager

	mpDeanSmurfSprites = new Sprite( mpDeanSpriteSheet, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_X, SMURF_SPRITE_DISPLACEMENT_FOR_CENTERING_Y, false, SMURF_DIMENSIONS );
	mpDeanSmurfWalkAnimation = new Animation(*mpDeanSmurfSprites,/* mGraphicsBufferManagement->getBuffer(3), mGraphicsBufferManagement,*/SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2(DISP_WIDTH, DISP_HEIGHT), SMURF_DIMENSIONS);

	// Create the display
	mpCurrentSystem->init( DISP_WIDTH, DISP_HEIGHT );
	
	// Set the boolean telling the program the display is running as true
	mIsDisplaying = true;
}


// This function calls system to initialize the allegro system
void Game::initializeSystems() 
{
	mpCurrentSystem->initializeSystems();
}


// This function cleans up and destroys all of the allegro systems
void Game::cleanup() 
{
	//delete the unit manager
	delete mpUnitManagement;
	mpUnitManagement = NULL;

	//delete the graphicsbuffer manager
	delete mpGraphicsBufferManagement;
	mpGraphicsBufferManagement = NULL;

	cleanExtra();//clean the game based pointers
	
	// Delete Display
	mpCurrentSystem->cleanup();

	// Set the boolean telling the program the display is running as true
	mIsDisplaying = false;
}

void Game::cleanExtra()
{
	//delete extra pointers
	delete mpDeanSmurfSprites;
	delete mpForest;
	delete mpSmurfSprites;

	// Delete Animations
	delete mpDeanSmurfWalkAnimation;
	delete mpSmurfWalkAnimation;
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
		mMouseInput = mpCurrentSystem->getMouseState();
		mKeyboardInput = mpCurrentSystem->getKeyState();

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
			//swap animations on all units
			if (mpCurrentSystem->getEnterChoice() == 0)
			{
				for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
				{
					mpUnitManagement->mpListOfUnits[i]->swapAnimation();
				}
			}
			//swap animations of the last sprite
			if (mpCurrentSystem->getEnterChoice() == 1)
			{
				mpUnitManagement->mpListOfUnits[mpUnitManagement->mpListOfUnits.size() - 1]->swapAnimation();
			}
		
		}

		// The following code checks if left mouse has been pressed. 
		// If it has and a certain unit is visible, move the unit to the mouse position
		if ( mMouseInput == mouse_left )
		{
			if (mpCurrentSystem->getLeftMouseChoice() == 0)
			{
					//call the unit manager's add unit function to add a new unit
					mpUnitManagement->addUnit();
	
					//set the new units animations to a new set of animations. -1 because of the index starting at 0
					mpUnitManagement->getUnit(mpUnitManagement->mNumUnits - 1)->setAnimation(new Animation(*mpSmurfWalkAnimation));//set the animation with smurf and dean animations
					mpUnitManagement->getUnit(mpUnitManagement->mNumUnits - 1)->setAnimation(new Animation(*mpDeanSmurfWalkAnimation));

					//move the newly added unit to the appropriate area, and change the location in sprites of that individual unit to match the mouse position.
					mpUnitManagement->getUnit(mpUnitManagement->mNumUnits - 1)->moveToMousePosition(mpCurrentSystem->getMousePosition());
					mpUnitManagement->getUnit(mpUnitManagement->mNumUnits - 1)->getCurrentAnimation()->getCurrentSprite()->changeLoc(mpCurrentSystem->getMousePosition().mX, mpCurrentSystem->getMousePosition().mY);
			}

			//moving unit
			else if (mpCurrentSystem->getLeftMouseChoice() == 1)
			{
				for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
				{
					if (mpUnitManagement->mpListOfUnits[i]->isVisible())
					{
						mpUnitManagement->mpListOfUnits[i]->moveToMousePosition(mpCurrentSystem->getMousePosition());
					}
				}
			}
			
		}

		// The following code checks if right mouse has been pressed. 
		// If it has and a certain unit is visible, delete the unit at that location
		if (mMouseInput == mouse_right)
		{
			for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
			{
				if (mpUnitManagement->mpListOfUnits[i]->isVisible())
				{
					if ((mpUnitManagement->mpListOfUnits[i]->returnLocation().mX  <= mpCurrentSystem->getMousePosition().mX  && mpUnitManagement->mpListOfUnits[i]->returnLocation().mY  >= mpCurrentSystem->getMousePosition().mY -20)
						  &&(mpUnitManagement->mpListOfUnits[i]->returnLocation().mX - 20 <= mpCurrentSystem->getMousePosition().mX  && mpUnitManagement->mpListOfUnits[i]->returnLocation().mY  <= mpCurrentSystem->getMousePosition().mY) - 20)
					{
						mpUnitManagement->removeUnit(i);
						max = mpUnitManagement->mpListOfUnits.size();
					}
				}
			}
		}

		// The following code checks if escape has been pressed. 
		// If it has, then speed up animation
		if ( mKeyboardInput == key_f ) 
		{
			for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
			{
				mpUnitManagement->mpListOfUnits[i]->changeAnimationSpeeds(-SMURF_WALK_SPEED_MODIFICATION_VALUE);
			}
		}

		// The following code checks if escape has been pressed. 
		// If it has, then slow down animation
		if ( mKeyboardInput == key_s ) 
		{
			for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
			{
				mpUnitManagement->mpListOfUnits[i]->changeAnimationSpeeds(SMURF_WALK_SPEED_MODIFICATION_VALUE);
			}
		}

		//The following code updates all units to either pause or resume their animations.
		if (mKeyboardInput == key_space)
		{
			for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
			{
				mpUnitManagement->mpListOfUnits[i]->toggleAnimationSpeeds();//for each unit, toggle their animations
			}
		}

		// The following code updates all of the units
		for (int i = 0, max = mpUnitManagement->mpListOfUnits.size(); i < max; i++)
		{
			mpUnitManagement->mpListOfUnits[i]->update(MAX_TIME_BETWEEN_FRAMES);
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
	mpCurrentSystem->getGraphicsSystem().draw( mBackgroundImage.getLoc(), mBackgroundImage, BACKGROUND_SCALING_VALUE ); // Draw the background image for the level

	// The following code draws an image to the back buffer 
	// based on where the sprites are located
	mpUnitManagement->drawAllUnits();

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
	mpCurrentSystem->flipDisplay();
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
	return mpCurrentSystem;
}

UnitManager * Game::getUnitManager()
{
	return mpUnitManagement;
}
