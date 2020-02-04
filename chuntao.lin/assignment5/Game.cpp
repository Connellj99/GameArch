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
	passedEventSystem->addListener((EventType)EXIT, this);
	passedEventSystem->addListener((EventType)CREATE, this);
	passedEventSystem->addListener((EventType)KILL, this);
	passedEventSystem->addListener((EventType)TOGGLE_ANIMATION, this);
	passedEventSystem->addListener((EventType)FLIP_ANIMATIONS, this);

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
	//mpsGameObject = new Game;//(EventSystem::getStaticEventSysInstance());
}





// This function destroys the current instance of the static class
void Game::destroyStaticGameInstance() 
{
	delete mpsGameObject;
}

// This function initializes all of the allegro systems
void Game::init()
{
	mpUnitManager = new UnitManager();//creating the new unit manager

	mpInputTrans = new InputTranslator(EventSystem::getStaticEventSysInstance());//creating the input translator

	// Initialize all systems
	initializeSystems();

	// Create the forest backgroud image
	mBufferManager.addBuffer(ASSET_PATH + FOREST_FILENAME, NAME_OF_FOREST_BUFFER);

	// Create the regular smurf animation
	mBufferManager.addBuffer(ASSET_PATH + SMURF_SPRITE_FILENAME, NAME_OF_SMURF_SPRITE_SHEET_BUFFER );
	mpSmurfWalkAnimation = new Animation( mBufferManager.getBuffer( NAME_OF_SMURF_SPRITE_SHEET_BUFFER ), SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2( DISP_WIDTH, DISP_HEIGHT ), SMURF_DIMENSIONS );

	// Create the dean smurf animation
	mBufferManager.addBuffer( ASSET_PATH + DEAN_SPRITE_FILENAME, NAME_OF_DEAN_SMURF_SPRITE_SHEET_BUFFER );
	mpDeanSmurfWalkAnimation = new Animation( mBufferManager.getBuffer( NAME_OF_DEAN_SMURF_SPRITE_SHEET_BUFFER ), SMURFS_SPRITES_PER_ROW, SMURFS_SPRITES_PER_COLUMN, Vector2( DISP_WIDTH, DISP_HEIGHT ), SMURF_DIMENSIONS );

	// Create the display
	mpSystem->init( DISP_WIDTH, DISP_HEIGHT );

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
	delete mpDeanSmurfWalkAnimation;
	delete mpSmurfWalkAnimation;

	// Delete Unit Manager
	delete mpUnitManager;

	//remove the listeners
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)EXIT, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)CREATE, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)KILL, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)TOGGLE_ANIMATION, this);
	EventSystem::getStaticEventSysInstance()->removeListener((EventType)FLIP_ANIMATIONS, this);

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
	/*bool inGame = true;*/
	Timer gameLoop;


	while ( inGame ) 
	{
		gameLoop.start(); // Start the timer

		mpInputSys->updateInput();//Get the input/update
	
		mpUnitManager->update( MAX_TIME_BETWEEN_FRAMES ); // Call update for all created units
		
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
	mpSystem->getGraphicsSystem().drawBackground( *mBufferManager.getBuffer(NAME_OF_FOREST_BUFFER), BACKGROUND_SCALING_VALUE );

	// Draw all units onto the back buffer
	mpUnitManager->draw();

	// Flip display after everything has been drawn to the back buffer
	flipDisplay();
}

void Game::handleEvent(const Event & passedEvent)
{
	if (passedEvent.getType() == EXIT)//if the heard type is exit, then set inGame bool to false, basically ending the do lopp
	{
		inGame = false;
	}

	if (passedEvent.getType() == CREATE)//if the heard type is create, then create a unit using the manager and add animations.
	{
		const CreateUnit& createEvent = static_cast<const CreateUnit&>(passedEvent);

		// Create a unit within the unit manager
		mpUnitManager->createUnit(createEvent.getLocation());

		// add both animations to the unit, the dean and smurf.
		mpUnitManager->addAnimation(mpUnitManager->getSize() - 1, *mpSmurfWalkAnimation);
		mpUnitManager->addAnimation(mpUnitManager->getSize() - 1, *mpDeanSmurfWalkAnimation);
	}

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
}





// This function flips the current display to go
// to the next frame
void Game::flipDisplay() 
{
	mpSystem->flipDisplay();
}





// This function gets the current system
System * Game::getCurrentSystem() 
{
	return mpSystem;
}