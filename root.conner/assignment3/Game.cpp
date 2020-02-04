/*
Conner Root
EGP 310 - 01
*/

#include "Game.h"

// Constructor
Game::Game()
{
}

// Init / Cleanup
void Game::init(int w, int h, float fR = 60)
{
	if (!mInited)
	{
		mFrameRate = fR;
		mTimePerFrame = 1000.0 / fR;

		mpSystem = new System();
		mpSystem->init(w, h);

		mpTimer = new Timer();

		mpWoodsBuffer = new GraphicsBuffer(ASSET_PATH + BACKGROUND_FILENAME);
		mpSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURFS_FILENAME);
		mpDeansBuffer = new GraphicsBuffer(ASSET_PATH + DEAN_FILENAME);

		mpWoodsSprite = new Sprite(mpWoodsBuffer, 0, 0, mpWoodsBuffer->getWidth(), mpWoodsBuffer->getHeight());
		/*mpSmurfSprite = new Sprite(mpSmurfBuffer,)
		Sprite* mpDeanSprite;*/

		mpSmurfAnim = new Animation(mpSmurfBuffer, SMURF_WIDTH, SMURF_HEIGHT, 1.0, true);
		mpDeanAnim = new Animation(mpDeansBuffer, SMURF_WIDTH, SMURF_HEIGHT, 1.0, true);

		int xPos = (w - SMURF_WIDTH) / 2;
		int yPos = (h - SMURF_HEIGHT) / 2;
		mpCharacter = new Unit(xPos, yPos, mpSmurfAnim);

		mInited = true;
	}
}

void Game::cleanup()
{
	if (mInited)
	{
		delete mpCharacter;
		delete mpSmurfAnim;
		delete mpDeanAnim;
		delete mpWoodsSprite;
		delete mpWoodsBuffer;
		delete mpSmurfBuffer;
		delete mpDeansBuffer;
		delete mpTimer;
		delete mpSystem;

		mInited = false;
	}
}

// Game Loop
void Game::gameLoop()
{
	mpTimer->start();

	getInput();
	update();
	drawScene();

	mpTimer->stop();
	waitForFrame(mTimePerFrame - mpTimer->getElapsedTime());
}

void Game::getInput()
{
	mMouseState = mpSystem->checkMouseDown();
	if (mMouseState.clicked)
		mpCharacter->setLocation(mMouseState.xPos, mMouseState.yPos);

	//mKeyState_F = mpSystem->checkKeyDown(F);
	if (mpSystem->checkKeyDown(F))
	{
		mpSmurfAnim->speedUp();
		mpDeanAnim->speedUp();
	}

	//mKeyState_S = mpSystem->checkKeyDown(S);
	if (mpSystem->checkKeyDown(S))
	{
		mpSmurfAnim->speedUp();
		mpDeanAnim->speedUp();
	}

	//mKeyState_Enter = mpSystem->checkKeyDown(ENTER);
	if(mpSystem->checkKeyDown(ENTER))
	{
		if (!mAnimDean)
		{
			mpCharacter->setAnimation(mpDeanAnim);
			mAnimDean = true;
		}
		else
		{
			mpCharacter->setAnimation(mpSmurfAnim);
			mAnimDean = false;
		}
	}

	//mKeyState_Exit = mpSystem->checkKeyDown(ESC);
	if (mpSystem->checkKeyDown(ESC))
		mShouldExit = true;
}

void Game::update()
{
	mpCharacter->update();
}

void Game::drawScene()
{
	mpSystem->getGraphicsSystem()->draw(0, 0, mpWoodsSprite, 1.0);
	mpCharacter->draw();
	mpSystem->getGraphicsSystem()->flipDisplay();
}

void Game::waitForFrame(float t)
{
	if (t > 0)
		al_rest(t / 1000.0);
}

// Destructor
Game::~Game()
{
	cleanup();
}

Game* pGameObj;