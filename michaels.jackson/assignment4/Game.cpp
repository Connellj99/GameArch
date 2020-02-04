/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Game.h"
#include "Unit.h"

Game* Game::mpGame = nullptr;

Game::Game()
{
	cout << ("creating") << endl;
	mSystem = new System();
}

Game::~Game()
{
	this->cleanUp();
	delete mSystem;
}

void Game::init(int width, int height)
{
	if (!mInit)
	{
		cout << ("initing") << endl;
		mSystem->init(width, height);
		mGBMan = new GraphicsBufferManager();
		mUnitMan = new UnitManager();
		mInit = true;
	}
}

void Game::cleanUp()
{
	if (mInit)
	{
		cout << ("Cleaning") << endl;
		mGBMan->clear();
		mUnitMan->clear();

		delete mGBMan;
		delete mUnitMan;

		mSystem->cleanUp();
		mInit = false;
	}
}

void Game::runGame(float fps)
{
	mGBMan->createBuffer("smurf_sprites.png", "smurfs");
	mGBMan->createBuffer("dean_sprites.png", "deans");
	mGBMan->createBuffer("Woods.png", "woods");


	Sprite woodsSprite(mGBMan->getBuffer("woods"), 0, 0);;

	Animation deanAnim(100);
	deanAnim.addSpriteSheet(mGBMan->getBuffer("deans"), 4, 4);

	Animation smurfAnim(100);
	smurfAnim.addSpriteSheet(mGBMan->getBuffer("smurfs"), 4, 4);

	bool exit = false;
	bool onSmurf = true;
	Timer time;
	MouseState mouse;

	double msPerFrame = (1.0 / fps) * 1000;


	while (!exit)
	{
		time.start();
		mSystem->clear();
		mSystem->mGraphics.draw(&woodsSprite, 0, 0, 0.5);
;		mouse = mSystem->getMouseState();

		if (mouse.left)
		{
			Animation* newAnim = new Animation(&smurfAnim);
			Unit* newUnit = new Unit(0, 0);
			newUnit->setAnimation(newAnim);
			newUnit->setLoc(mouse.loc);
			mUnitMan->addUnit(newUnit);
		}
		if (mouse.right)
		{
			mUnitMan->deleteUnitAt(mouse.loc);
		}
		if (mSystem->getKeyState(KEY_ENTER) && mUnitMan->getNumUnits() > 0)
		{
			if (onSmurf)
			{
				mUnitMan->getLast()->setAnimation(new Animation(deanAnim));
			}
			else
			{
				mUnitMan->getLast()->setAnimation(new Animation(smurfAnim));
			}
			onSmurf = !onSmurf;
		}

		if (mSystem->getKeyState(KEY_SPACE))
		{
			for (int i = 0; i < mUnitMan->getNumUnits(); i++)
			{
				mUnitMan->getUnit(i)->toggleAnimate();
			}
		}

		mUnitMan->update(msPerFrame);

		mUnitMan->draw();

		if (mSystem->getKeyState(KEY_ESCAPE))
		{
			exit = true;
		}


		mSystem->mGraphics.flip();
		time.sleepUntilElapsed(msPerFrame);
		cout << time.getElapsedTime() << endl;

	}

}