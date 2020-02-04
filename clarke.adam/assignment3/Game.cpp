#include "Game.h"

Game* gpGame;

Game::Game()
	: mAnimIsDean(false), mpWoodsBuffer(nullptr),
	mpSmurfsBuffer(nullptr), mpDeanSmurfsBuffer(nullptr), mpWoodsSprite(nullptr), mpSmurfAnimation(nullptr),
	mpDeanSmurfAnimation(nullptr), mpSmurfUnit(nullptr)
{
	mpSystem = new System();
	mpTimer = new Timer();
}

Game::~Game()
{
	cleanup();

	delete mpSystem;
	delete mpTimer;
}

void Game::init(const Vector2D& displayDimensions, float targetFrameRate)
{
	mIsInitted = true;

	mpSystem->init(displayDimensions);

	mMsPerFrame = 1000 / targetFrameRate;
	mShouldExit = false;
	// start timer used to measure loop time
	mpTimer->start();

	// woods image buffer
	mpWoodsBuffer = new GraphicsBuffer(ASSET_PATH + WOODS_FILENAME);
	// sprite of entire woods buffer
	mpWoodsSprite = new Sprite(mpWoodsBuffer, Vector2D(0, 0), mpWoodsBuffer->getDimensions());
	// set woods scale to match display size
	mWoodsScale = Vector2D(mpSystem->getGraphicsSystem()->getDisplayWidth() / mpWoodsSprite->getDimensions().getX(),
		mpSystem->getGraphicsSystem()->getDisplayHeight() / mpWoodsSprite->getDimensions().getY());

	// smurf spritesheet buffer
	mpSmurfsBuffer = new GraphicsBuffer(ASSET_PATH + SMURFS_FILENAME);
	// dean smurf spritesheet buffer
	mpDeanSmurfsBuffer = new GraphicsBuffer(ASSET_PATH + DEAN_SMURFS_FILENAME);
	// create looping animations from spritesheet buffers
	mpSmurfAnimation = new Animation(mpSmurfsBuffer, SMURF_SPRITE_SIZE, SMURF_ANIMATION_SPEED_INIT, true);
	mpDeanSmurfAnimation = new Animation(mpDeanSmurfsBuffer, SMURF_SPRITE_SIZE, SMURF_ANIMATION_SPEED_INIT, true);
	// create smurf unit w/ initial smurf animation & initial position in center of display
	mpSmurfUnit = new Unit(mpSmurfAnimation, mpSystem->getGraphicsSystem()->getDisplayDimensions() * 0.5f - SMURF_SPRITE_SIZE * 0.5f, SMURF_SCALE);
}

void Game::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	delete mpSmurfUnit;
	delete mpSmurfAnimation;
	delete mpDeanSmurfAnimation;
	delete mpWoodsSprite;

	delete mpDeanSmurfsBuffer;
	delete mpSmurfsBuffer;
	delete mpWoodsBuffer;

	mKeysDown.clear();

	mpSystem->cleanup();
}

void Game::doLoop()
{
	// time this loop
	mpTimer->start();

	processInput();
	update();
	render();

	// sleep until mMsPerFrame since loop start to run at target fps
	mpTimer->sleepUntilElapsed(mMsPerFrame);
}

void Game::update()
{
	// move smurf unit on left mouse click
	if (mMouseState.isDown)
	{
		mpSmurfUnit->setLocation(mMouseState.location - SMURF_SPRITE_SIZE * 0.5f);
	}

	// switch smurf unit's animation when enter key is down
	if (mKeysDown[ENTER])
	{
		mpSmurfUnit->setAnimation(mAnimIsDean ? mpSmurfAnimation : mpDeanSmurfAnimation);
		mAnimIsDean = !mAnimIsDean;
	}

	// speed up animations when f key is down
	if (mKeysDown[F])
	{
		mpSmurfAnimation->setSpeed(mpSmurfAnimation->getSpeed() + SMURF_ANIMATION_SPEED_INCREMENT);
		mpDeanSmurfAnimation->setSpeed(mpDeanSmurfAnimation->getSpeed() + SMURF_ANIMATION_SPEED_INCREMENT);
	}

	// slow down animations when s key is down
	if (mKeysDown[S])
	{
		// no negative speed
		auto newSpeed = mpSmurfAnimation->getSpeed() - SMURF_ANIMATION_SPEED_INCREMENT;
		if (newSpeed < 0)
		{
			newSpeed = 0;
		}

		mpSmurfAnimation->setSpeed(newSpeed);
		mpDeanSmurfAnimation->setSpeed(newSpeed);
	}

	// exit game on esc press
	if (mKeysDown[ESC])
	{
		mShouldExit = true;
	}

	mpSmurfUnit->update();
}

void Game::processInput()
{
	// get current mouse and keyboard states
	mMouseState = mpSystem->getMouseState(1);
	mKeysDown[ENTER] = mpSystem->getKeyState(ENTER);
	mKeysDown[F] = mpSystem->getKeyState(F);
	mKeysDown[S] = mpSystem->getKeyState(S);
	mKeysDown[ESC] = mpSystem->getKeyState(ESC);
}

void Game::render()
{
	// draw scaled woods background to backbuffer
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, mWoodsScale);
	// draw smurf unit to backbuffer
	mpSmurfUnit->draw();

	// flip backbuffer to display
	mpSystem->getGraphicsSystem()->flip();
}

