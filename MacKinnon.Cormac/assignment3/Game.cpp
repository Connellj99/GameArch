#include "Game.h"

Game* gpGame = NULL;
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
//initializes the game and creates the necessary buffers, animations, units, and sprites and creates the display
void Game::init()
{
	mIsInit = true;

	mpSystem->init(DISP_WIDTH, DISP_HEIGHT);
	mpWoodsBuffer = new GraphicsBuffer(ASSET_PATH + FOREST_IMAGE);
	mpWoodsSprite = new Sprite(0, 0, mpWoodsBuffer->getWidth(), mpWoodsBuffer->getHeight(), mpWoodsBuffer);
	
	mpSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURFS_IMAGE);
	mpDeanBuffer = new GraphicsBuffer(ASSET_PATH + DEAN_IMAGE);

	mpSmurfAnim = new Animation(mpSmurfBuffer, SMURF_WIDTH, SMURF_HEIGHT, SMURF_ROWS, SMURF_COLS, true);
	mpDeanAnim = new Animation(mpDeanBuffer, SMURF_WIDTH, SMURF_HEIGHT, SMURF_ROWS, SMURF_COLS, true);

	mpSmurfObject = new Unit(Vector2D(((DISP_WIDTH) / 2.0) - mpSmurfAnim->getCurrentSprite()->getWidth() / 2, ((DISP_HEIGHT / 2) - mpSmurfAnim->getCurrentSprite()->getHeight() / 2)));
	mpSmurfObject->addAnimation(mpSmurfAnim);
	mpSmurfObject->addAnimation(mpDeanAnim);
}
//destroys the program properly
void Game::cleanup()
{
	if (!mIsInit)
		return;
	//delete mpTimer;
	delete mpSmurfObject;
	delete mpDeanAnim;
	delete mpSmurfAnim;
	delete mpWoodsSprite;
	delete mpDeanBuffer;
	delete mpSmurfBuffer;
	delete mpWoodsBuffer;
	
	mpSystem->cleanup();

	mIsInit = false;
}
//game loop function that keeps track of the frame time
void Game::doLoop()
{
	Timer timer;

	while (!mExitGame)
	{
		timer.start();
		getInput();
		update();
		render();

		timer.sleepUntilElapsed(FRAME_TIME);
		std::cout << "Frame Time: " << timer.getElapsedTime() << "ms\n";
		timer.stop();
	}
}
//determines whether or not a key or mouse button has been pressed and enables the function associated with the key
void Game::getInput()
{
	mIsMouseDown = mpSystem->getMouseState();


	if (mIsMouseDown)
	{
		if (mpSmurfObject->isVisible())
		{
			mpSmurfObject->setUnitLocation(mpSystem->getMousePos() - Vector2D(SMURF_WIDTH, SMURF_HEIGHT) * 0.5f);
		}
	}

	if (mpSystem->getKeyState(F_KEY))
	{
		//makes sure the key only activates once when pressed to prevent issues of infinite inputs
		if (!mFPressed)
		{
			mpSmurfAnim->speedUpAnimation();
			mpDeanAnim->speedUpAnimation();
			mFPressed = true;
		}
	}
	else
	{
		mFPressed = false;
	}

	if (mpSystem->getKeyState(S_KEY))
	{
		if (!mSPressed)
		{
			mpSmurfAnim->speedDownAnimation();
			mpDeanAnim->speedDownAnimation();
			mSPressed = true;
		}
	}
	else
	{
		mSPressed = false;
	}

	if (mpSystem->getKeyState(ENTER_KEY))
	{
		if (!mEnterPressed)
		{
			mpSmurfObject->setAnimation();
		}
	}
	else
	{
		mEnterPressed = false;
	}

	if (mpSystem->getKeyState(ESCAPE_KEY))
	{
		mExitGame = true;
	}
}

//updates the unit
void Game::update()
{
	mpSmurfObject->update();
}
//draws all necessary parts onto the back buffer and then flips the screen so they are visible
void Game::render()
{
	mpSystem->getGraphicsSystem()->draw(0.0f, 0.0f, mpWoodsSprite, SCALE_FACTOR);

	mpSmurfObject->draw();

	mpSystem->getGraphicsSystem()->flipDisplay();
}
//accessor
System* Game::getSystem()
{
	return mpSystem;
}
