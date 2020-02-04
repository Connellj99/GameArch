/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Game.h"
#include "Unit.h"

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
	GraphicsBuffer woodsBuff("Woods.png");
	GraphicsBuffer deanBuff("dean_sprites.png");
	GraphicsBuffer smurfBuff("smurf_sprites.png");

	Animation deanAnim(100);
	deanAnim.addSpriteSheet(&deanBuff, 4, 4);

	Animation smurfAnim(100);
	smurfAnim.addSpriteSheet(&smurfBuff, 4, 4);

	Unit pawn(mSystem->mGraphics.getWindowWidth() / 2, mSystem->mGraphics.getWindowHeight() / 2);
	pawn.setAnimation(&smurfAnim);

	bool exit = false;
	bool onSmurf = true;
	Timer time;
	MouseState mouse;

	double msPerFrame = (1.0 / fps) * 1000;

	while (!exit)
	{
		time.start();
		mSystem->clear();
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

		mSystem->mGraphics.flip();
		time.sleepUntilElapsed(msPerFrame);
	}

	mSystem->cleanUp();
}

Game* gpGame = new Game();