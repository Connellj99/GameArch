#include "Game.h"

Input Game::checkInput()
{
	Input temp;
	if (mSystem->getKeyDown(ESCAPE))
	{
		temp.escKey = true;
	}
	if (mSystem->getKeyDown(ENTER))
	{
		temp.enterKey = true;
	}
	if (mSystem->getKeyDown(F))
	{
		temp.fKey = true;
	}
	if (mSystem->getKeyDown(S))
	{
		temp.sKey = true;
	}
	if (mSystem->getButtonDown(Left_Click).down)
	{
		temp.leftClick = true;
		temp.clickPos = mSystem->getButtonDown(Left_Click).position;
	}
	return temp;
}

void Game::render()
{
	mSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpWoodsSprite, WOODS_SCALE);
	mUnit.draw();
	mSystem->getGraphicsSystem()->flip();
}

void Game::update(Input currentInput)
{
	if (currentInput.escKey)
	{
		mLoopGame = false;
	}
	if (currentInput.enterKey)
	{
		mUnit.swapAnimations();
	}
	if (currentInput.fKey)
	{
		mUnit.getCurrentAnimation().speedUp(SPEED_CHANGE);
	}
	if (currentInput.sKey)
	{
		mUnit.getCurrentAnimation().slowDown(SPEED_CHANGE);
	}
	if (currentInput.leftClick)
	{
		mUnit.updateLocation(currentInput.clickPos);
	}
	mUnit.update();
}


Game::Game()
{
	mpDeanSpriteSheet = nullptr;
	mpSmurfSpriteSheet = nullptr;
	mpWoodsBuffer = nullptr;
	mpWoodsSprite = nullptr;
}

Game::~Game()
{
	cleanup();
}

void Game::doLoop()
{
	mTimer.start();

	Input currentInput = checkInput();
	update(currentInput);
	render();


	mTimer.sleepUntilElapsed(mframeTime);
}

void Game::init(Vector2D screenSize, float targetFrameRate)
{
	mSystem = new System();
	mSystem->init();
	//Set screen and frame variables
	mScreenSize = screenSize;
	mframeTime = 1000 / targetFrameRate;
	//create background buffer
	mpWoodsBuffer = new GraphicsBuffer(SHARED_PATH + BACKGROUND_FILENAME);
	mpWoodsSprite = new Sprite(mpWoodsBuffer, Vector2D(0, 0), Vector2D(mpWoodsBuffer->getWidth(), mpWoodsBuffer->getHeight()));
	//create smurf buffers
	mpSmurfSpriteSheet = new GraphicsBuffer(SHARED_PATH + SMURF_FILENAME);
	mpDeanSpriteSheet = new GraphicsBuffer(SHARED_PATH + DEAN_FILENAME);
	//create temp animation vector to pass to unit
	vector<Animation> temp;
	temp.push_back(Animation(*mpSmurfSpriteSheet, SMURF_SPRITE_SIZE));
	temp.push_back(Animation(*mpDeanSpriteSheet, SMURF_SPRITE_SIZE));
	//load animations into unit
	mUnit = Unit(temp, mScreenSize*0.5f);


}

void Game::cleanup()
{
	delete mpSmurfSpriteSheet;
	delete mpDeanSpriteSheet;
	delete mpWoodsBuffer;
	delete mpWoodsSprite;
	mpSmurfSpriteSheet = nullptr;
	mpDeanSpriteSheet = nullptr;
	mpWoodsBuffer = nullptr;
	mpWoodsSprite = nullptr;
	mSystem->cleanup();
	delete mSystem;
	mSystem = nullptr;
}

System* Game::getSystem()
{
	return mSystem;
}
