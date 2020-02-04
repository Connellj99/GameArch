#include "Game.h"

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
	mpsGame = new Game();
}

void Game::cleanupInstance()
{
	delete mpsGame;
}

//initializes the game and creates the necessary buffers, animations, units, and sprites and creates the display
void Game::init()
{
	mIsInit = true;

	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);

	mpUnitManager = new UnitManager();
	mpGraphicsBufferManager = new GraphicsBufferManager();

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

	mpsGame->getSystem()->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY), SCALE_FACTOR);
}

//destroys the program properly
void Game::cleanup()
{
	if (!mIsInit)
		return;

	mpSystem->cleanup();

	
	delete mpUnitManager;
	delete mpGraphicsBufferManager;

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
		mInput = getInput();
		update();
		render();

		timer.sleepUntilElapsed(FRAME_TIME);
		std::cout << "Frame Time: " << timer.getElapsedTime() << "ms\n";
		timer.stop();
	}
}
//determines whether or not a key or mouse button has been pressed and enables the function associated with the key
int Game::getInput()
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
}

//updates the unit
void Game::update()
{
	if (mInput == LEFT_CLICK) 
	{
		Vector2D mouseLoc = mpsGame->getSystem()->getMousePos();
		mpUnitManager->addUnit(mouseLoc, mpSmurfList);
		mpUnitManager->getUnit()->addAnimation(mpDeanList);
	}
	if (mInput == RIGHT_CLICK)
	{
		Vector2D mouseLoc = mpsGame->getSystem()->getMousePos();
		mpUnitManager->removeUnits(mouseLoc);
	}
	if (mInput == F)
	{
		mpUnitManager->getUnit()->getCurrentAnimation()->speedUpAnimation();
	}
	if (mInput == S)
	{
		mpUnitManager->getUnit()->getCurrentAnimation()->speedDownAnimation();

	}
	if (mInput == ENTER)
	{
		mpUnitManager->getUnit()->setAnimation();
	}
	if (mInput == SPACE)
	{
		mpUnitManager->toggleAnimationActive();
	}
	if (mInput == ESCAPE)
	{
		mExitGame = true;
	}
	mpUnitManager->update(FRAME_TIME);
}
//draws all necessary parts onto the back buffer and then flips the screen so they are visible
void Game::render()
{
	mpsGame->getSystem()->getGraphicsSystem()->draw(0.0f, 0.0f, mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY), SCALE_FACTOR);
	//mpSystem->getGraphicsSystem()->draw(0.0f, 0.0f, mpWoodsSprite, SCALE_FACTOR);

	mpUnitManager->draw();

	mpSystem->getGraphicsSystem()->flipDisplay();
}
//accessor
System* Game::getSystem()
{
	return mpSystem;
}
