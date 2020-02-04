/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#include "Unit.h"
#include "Game.h"

Game::Game()
{
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
		mSystem->init(width, height);
		mInit = true;
	}
}

void Game::cleanUp()
{
	if (mInit)
	{
		mSystem->cleanUp();
		mInit = false;
	}
}

void Game::runGame(float fps)
{
	GraphicsBuffer woodsBuffer("Woods.png");
	GraphicsBuffer deanBuffer("dean_sprites.png");
	GraphicsBuffer smurfBuffer("smurf_sprites.png");

	Animation deanAnim(100);
	deanAnim.addSpriteSheet(&deanBuffer, 4, 4);

	Animation smurfAnim(100);
	smurfAnim.addSpriteSheet(&smurfBuffer, 4, 4);

	woodsSprite = new Sprite(0, 0, woodsBuffer.getWidth(), woodsBuffer.getHeight(), &woodsBuffer);

	Unit pawn(mSystem->mGraphics.getWidth() / 2, mSystem->mGraphics.getHeight() / 2);
	pawn.setAnimation(&smurfAnim);

	bool exit = false;
	bool onSmurf = true;
	Timer time;
	MouseState mouse;

	double msPerFrame = (1.0 / fps) * 1000;

	while (!exit)
	{
		time.start();
		mSystem->mGraphics.draw(0, 0, woodsSprite);
		mouse = mSystem->getMouseState();

		if (mouse.left)
		{
			pawn.setLoc(mouse.loc);
		}

		if (mSystem->getKeyState(KEY_F))
		{
			pawn.getAnimation()->adjSpeed(-50);
		}
		if (mSystem->getKeyState(KEY_S))
		{
			pawn.getAnimation()->adjSpeed(50);
		}

		if (mSystem->getKeyState(KEY_ENTER))
		{
			if (onSmurf)
			{
				pawn.setAnimation(&deanAnim);
			}
			else
			{
				pawn.setAnimation(&smurfAnim);
			}
			onSmurf = !onSmurf;
		}

		pawn.update(msPerFrame);

		pawn.draw();

		if (mSystem->getKeyState(KEY_ESCAPE))
		{
			exit = true;
		}

		mSystem->mGraphics.Flip();
		time.sleepUntilElapsed(msPerFrame);
	}

	mSystem->cleanUp();
}

Game* gpGame = new Game();