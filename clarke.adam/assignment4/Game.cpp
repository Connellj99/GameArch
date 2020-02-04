#include "Game.h"

Game* Game::mpsGame = nullptr;

Game::Game()
{
	mpSystem = new System();
	mpUnitManager = new UnitManager();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpTimer = new Timer();
	mpPerformanceTracker = new PerformanceTracker();
}

Game::~Game()
{
	cleanup();

	delete mpTimer;
	delete mpGraphicsBufferManager;
	delete mpUnitManager;
	delete mpSystem;
	delete mpPerformanceTracker;
}

Game* Game::getInstance()
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

void Game::init(const Vector2D& displayDimensions, float targetFrameRate)
{
	mIsInitted = true;

	mpSystem->init(displayDimensions);

	mMsPerFrame = 1000 / targetFrameRate;
	mShouldExit = false;
	// start timer used to measure loop time
	mpTimer->start();

	// manage back buffer
	mpGraphicsBufferManager->addGraphicsBuffer(BACK_BUFFER_KEY,
		mpSystem->getGraphicsSystem()->getBackBuffer(), false);
	// woods image buffer
	mpGraphicsBufferManager->createGraphicsBuffer(WOODS_BUFFER_KEY, ASSET_PATH + WOODS_FILENAME);
	// sprite of entire woods buffer
	const auto woodsBuffer = mpGraphicsBufferManager->getGraphicsBuffer(WOODS_BUFFER_KEY);
	mpWoodsSprite = new Sprite(woodsBuffer, Vector2D(0, 0), woodsBuffer->getDimensions());
	// set woods scale to match display size
	mWoodsScale = Vector2D(mpSystem->getGraphicsSystem()->getDisplayWidth() / mpWoodsSprite->getDimensions().getX(),
		mpSystem->getGraphicsSystem()->getDisplayHeight() / mpWoodsSprite->getDimensions().getY());

	// smurf spritesheet buffer
	mpGraphicsBufferManager->createGraphicsBuffer(SMURF_BUFFER_KEY, ASSET_PATH + SMURFS_FILENAME);
	// dean smurf spritesheet buffer
	mpGraphicsBufferManager->createGraphicsBuffer(DEAN_SMURF_BUFFER_KEY, ASSET_PATH + DEAN_SMURFS_FILENAME);
	mAnimIsDean = false;
}

void Game::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	delete mpWoodsSprite;

	mKeysDown.clear();

	mpGraphicsBufferManager->clear();
	mpUnitManager->clear();
	mpSystem->cleanup();
}

void Game::doLoop()
{
	while (!getShouldExit())
	{
		mpPerformanceTracker->clearTracker(LOOP_TRACKER);
		mpPerformanceTracker->startTracking(LOOP_TRACKER);

		// time this loop
		mpTimer->start();

		processInput();
		update();
		render();

		// sleep until mMsPerFrame since loop start to run at target fps
		mpTimer->sleepUntilElapsed(mMsPerFrame);

		mpPerformanceTracker->stopTracking(LOOP_TRACKER);
		std::cout << "loop time: " << mpPerformanceTracker->getElapsedTime(LOOP_TRACKER) << " ms" << std::endl;
	}
}

void Game::update()
{
	// create smurf unit at left mouse click
	if (mMouseState.m1IsDown)
	{
		Animation smurfAnimation(mpGraphicsBufferManager->getGraphicsBuffer(SMURF_BUFFER_KEY),
			SMURF_SPRITE_SIZE, SMURF_ANIMATION_SPEED_INIT, true);
		Animation deanSmurfAnimation(mpGraphicsBufferManager->getGraphicsBuffer(DEAN_SMURF_BUFFER_KEY),
			SMURF_SPRITE_SIZE, SMURF_ANIMATION_SPEED_INIT, true);
		std::map<std::string, Animation> smurfAnimations
		{
			{ SMURF_ANIMATION_NAME, smurfAnimation },
			{ DEAN_SMURF_ANIMATION_NAME, deanSmurfAnimation }
		};
		mpCurSmurfUnit = mpUnitManager->createUnit(smurfAnimations, mMouseState.location - SMURF_SPRITE_SIZE * 0.5f, SMURF_SCALE);
		// set new smurf unit's initial animation to regular smurf
		mpCurSmurfUnit->setAnimation(SMURF_ANIMATION_NAME);
	}

	// delete smurfs at right mouse click
	if(mMouseState.m2IsDown)
	{
		auto clickedSmurfs = mpUnitManager->getUnits(mMouseState.location);
		for (auto smurf : clickedSmurfs)
		{
			// destroy clicked smurfs, if most recently added smurf was deleted, set it to nullptr
			if(mpUnitManager->destroyUnit(smurf))
			{
				mpCurSmurfUnit = nullptr;
			}
		}
	}

	// switch most recent smurf unit's animation when enter key is down
	if (mKeysDown[ENTER])
	{
		if (mpCurSmurfUnit)
		{
			const auto newAnim = mAnimIsDean ? SMURF_ANIMATION_NAME : DEAN_SMURF_ANIMATION_NAME;
			mpCurSmurfUnit->setAnimation(newAnim);
			mAnimIsDean = !mAnimIsDean;
		}
	}

	// toggle all smurfs' animations on Space
	if (mKeysDown[SPACE])
	{
		mpUnitManager->toggleAnimations();
	}

	// exit game on esc press
	if (mKeysDown[ESC])
	{
		mShouldExit = true;
	}

	// update all smurfs' animations
	mpUnitManager->update();
}

void Game::processInput()
{
	// get current mouse and keyboard states
	mMouseState = mpSystem->getMouseState();
	mKeysDown[ENTER] = mpSystem->getKeyState(ENTER);
	mKeysDown[F] = mpSystem->getKeyState(F);
	mKeysDown[S] = mpSystem->getKeyState(S);
	mKeysDown[ESC] = mpSystem->getKeyState(ESC);
	mKeysDown[SPACE] = mpSystem->getKeyState(SPACE);
}

void Game::render()
{
	// draw scaled woods background to backbuffer
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, mWoodsScale);

	// draw all smurfs
	mpUnitManager->draw();

	// flip backbuffer to display
	mpSystem->getGraphicsSystem()->flip();
}

