
/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "System.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"

static class Game : public Trackable
{
public:
	static Game* getInstance() { assert(mpGame != nullptr); return mpGame; };
	static void initInstance() { mpGame = new Game; };
	static void cleanupInstance() { delete mpGame; };


	Game();
	~Game();
	void init(int = 600, int = 600);
	void cleanUp();

	void runGame(float fps = 60);

	System* getSystem() { return mSystem; };

private:
	UnitManager* mUnitMan;
	GraphicsBufferManager* mGBMan;
	System* mSystem;
	bool mInit = false;
	double mTimePerFrame;
	static Game* mpGame;
};

