#include "Game.h"
#include "Event.h"
#include "EventSystem.h"
#include "MouseClickEvent.h"
#include "KeyPressEvent.h"
#include "CreateUnitEvent.h"
#include "DeleteUnitEvent.h"
#include "SwapAnimationEvent.h"
#include "ExitGameEvent.h"
#include "ToggleAnimationActiveEvent.h"

Game* Game::mpsGame = nullptr;
//constructor
Game::Game()
{
	mpSystem = new System();
}

//destructor
Game::~Game()
{
	cleanup();
}

//static class related functions
Game * Game::getInstance()
{
	assert(mpsGame != nullptr);
	return mpsGame;
}

void Game::initInstance()
{
	if (mpsGame == nullptr)
	{
		mpsGame = new Game();
	}
}

void Game::cleanupInstance()
{
	delete mpsGame;
}

//initializes the game and creates the necessary buffers, animations, units, and sprites and creates the display
void Game::init()
{
	mIsInit = true;

	auto eventSystem = EventSystem::getInstance();

	eventSystem->addListener(EventType(CREATE_UNIT_EVENT), this);
	eventSystem->addListener(EventType(SWAP_ANIMATION_EVENT), this);
	eventSystem->addListener(EventType(TOGGLE_ANIMATION_ACTIVE_EVENT), this);
	eventSystem->addListener(EventType(DESTROY_UNIT_EVENT), this);
	eventSystem->addListener(EventType(EXIT_GAME_EVENT), this);

	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);

	mpUnitManager = new UnitManager();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpInputTranslator = new InputTranslator();
	mpInputTranslator->init();

	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + FOREST_IMAGE, WOODS_BUFFER_KEY);
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + SMURFS_IMAGE, SMURF_BUFFER_KEY);
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + DEAN_IMAGE, DEAN_BUFFER_KEY);

	mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY);
	

	for (int x = 0; x < SMURF_COLS; x++) 
	{
		for (int y = 0; y < SMURF_ROWS; y++) 
		{
			mpSmurfList.push_back(new Sprite((x * SMURF_WIDTH), (y * SMURF_HEIGHT), SMURF_WIDTH, SMURF_HEIGHT, mpGraphicsBufferManager->getGraphicsBuffer(SMURF_BUFFER_KEY)));
			mpDeanList.push_back(new Sprite((x * SMURF_WIDTH), (y * SMURF_HEIGHT), SMURF_WIDTH, SMURF_HEIGHT, mpGraphicsBufferManager->getGraphicsBuffer(DEAN_BUFFER_KEY)));
		}
	}

	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + SMURFS_IMAGE, SMURF_BUFFER_KEY);
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH + DEAN_IMAGE, DEAN_BUFFER_KEY);

	mpsGame->getSystem()->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY), SCALE_FACTOR);
}

//destroys the program properly
void Game::cleanup()
{
	if (!mIsInit)
		return;
	
	delete mpUnitManager;
	delete mpGraphicsBufferManager;
	delete mpInputTranslator;

	mpSystem->cleanup();

	for (unsigned int i = 0; i < mpSmurfList.size(); i++) 
	{
		delete mpSmurfList[i];
	}
	for (unsigned int i = 0; i < mpDeanList.size(); i++) 
	{
		delete mpDeanList[i];
	}

	

	mIsInit = false;
}
//game loop function that keeps track of the frame time
void Game::doLoop()
{
	Timer timer;

	while (!mExitGame)
	{
		timer.start();
		//mInput = getInput();
		update();
		render();

		timer.sleepUntilElapsed(FRAME_TIME);
		std::cout << "Frame Time: " << timer.getElapsedTime() << "ms\n";
		timer.stop();
	}
}
//determines whether or not a key or mouse button has been pressed and enables the function associated with the key
/*int Game::getInput()
{
	//mIsMouseDown = mpSystem->getMouseState();
	if (mpSystem->getMouseState(LEFT_CLICK)) 
	{
		return LEFT_CLICK;
	}
	if (mpSystem->getMouseState(RIGHT_CLICK)) 
	{
		return RIGHT_CLICK;
	}
	if (mpSystem->getKeyState(F)) 
	{
		return F;
	}
	if (mpSystem->getKeyState(S))
	{
		return S;
	}
	if (mpSystem->getKeyState(ENTER))
	{
		return ENTER;
	}
	if (mpSystem->getKeyState(SPACE))
	{
		return SPACE;
	}
	if (mpSystem->getKeyState(ESCAPE))
	{
		return ESCAPE;
	}
}*/

//updates the unit
void Game::update()
{	
	mpSystem->update(FRAME_TIME);

	mpUnitManager->update(FRAME_TIME);
}
//draws all necessary parts onto the back buffer and then flips the screen so they are visible
void Game::render()
{
	mpsGame->getSystem()->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY), SCALE_FACTOR);

	mpUnitManager->draw();

	mpSystem->getGraphicsSystem()->flipDisplay();
}
//has the events complete their appropriate action
void Game::handleEvent(const Event& theEvent)
{
	if (EventType(theEvent.getType()) == CREATE_UNIT_EVENT) 
	{
		auto createUnitEvent = dynamic_cast<const CreateUnitEvent&>(theEvent);
		mpUnitManager->addUnit(createUnitEvent.getMousePos(), mpSmurfList);
		mpUnitManager->getUnit()->addAnimation(mpDeanList);
	}
	else if (EventType(theEvent.getType()) == DESTROY_UNIT_EVENT) 
	{
		auto deleteUnitEvent = dynamic_cast<const DeleteUnitEvent&>(theEvent);
		mpUnitManager->removeUnits(deleteUnitEvent.getMousePos());
	}
	else if (EventType(theEvent.getType()) == SWAP_ANIMATION_EVENT) 
	{
		mpUnitManager->getUnit()->setAnimation();
	}
	else if (EventType(theEvent.getType()) == TOGGLE_ANIMATION_ACTIVE_EVENT) 
	{
		mpUnitManager->toggleAnimationActive();
	}
	else if (EventType(theEvent.getType()) == EXIT_GAME_EVENT) 
	{
		mExitGame = true;
	}
}
//accessor
System* Game::getSystem()
{
	return mpSystem;
}
