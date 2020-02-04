/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Game.h"
#include "Unit.h"
#include "InputTranslator.h"

Game* Game::mpGame = nullptr;

Game::Game(EventSystem* pEventSystem) : EventListener(pEventSystem)
{
	getEventSystem()->addListener(SPAWN_UNIT, this);
	getEventSystem()->addListener(DELETE_UNIT, this);
	getEventSystem()->addListener(STOP_ANIM, this);
	getEventSystem()->addListener(CHANGE_ANIM, this);
	getEventSystem()->addListener(EXIT, this);
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

void Game::handleEvent(const Event& theEvent) {
	cout << theEvent.getEventName() << endl;
	switch (theEvent.getType())
	{
	case SPAWN_UNIT:
		{
		const SpawnEvent& ev = static_cast<const SpawnEvent&>(theEvent);
		Animation* animation = new Animation(100);
		animation->addSpriteSheet(mGBMan->getBuffer("smurfs"), 4, 4);
		Unit* newUnit = new Unit(0, 0);
		newUnit->setAnimation(animation);
		newUnit->setLoc(ev.getLoc());
		mUnitMan->addUnit(newUnit);
		}
		break;

	case DELETE_UNIT:
		{
			const DeleteEvent& ev = static_cast<const DeleteEvent&>(theEvent);
			mUnitMan->deleteUnitAt(ev.getLoc());
		}
		break;

	case STOP_ANIM:
		for (int i = 0; i < mUnitMan->getNumUnits(); i++)
		{
			mUnitMan->getUnit(i)->toggleAnimate();
		}
		break;

	case CHANGE_ANIM:
		{Animation* newAnim = new Animation(100);
		delete mUnitMan->getLast()->getAnimation();
		if (mSmurf)
		{
			newAnim->addSpriteSheet(mGBMan->getBuffer("deans"), 4, 4);
			mUnitMan->getLast()->setAnimation(new Animation(newAnim));
		}
		else
		{
			newAnim->addSpriteSheet(mGBMan->getBuffer("smurfs"), 4, 4);
			mUnitMan->getLast()->setAnimation(new Animation(newAnim));
		}
		mSmurf = !mSmurf;
		}
		break;

	case EXIT:
		mExit = true;
		break;
	}
}

void Game::runGame(float fps)
{
	mGBMan->createBuffer("smurf_sprites.png", "smurfs");
	mGBMan->createBuffer("dean_sprites.png", "deans");
	mGBMan->createBuffer("Woods.png", "woods");


	Sprite woodsSprite(mGBMan->getBuffer("woods"), 0, 0);


	Timer time;
	MouseState mouse;

	double msPerFrame = (1.0 / fps) * 1000;


	while (!mExit)
	{
		time.start();
		mSystem->clear();
		mSystem->mGraphics.draw(&woodsSprite, 0, 0, 0.5);
		

		mUnitMan->update(msPerFrame);
		mSystem->update();

		mUnitMan->draw();

		


		mSystem->mGraphics.flip();
		time.sleepUntilElapsed(msPerFrame);
		cout << time.getElapsedTime() << endl;

	}

}