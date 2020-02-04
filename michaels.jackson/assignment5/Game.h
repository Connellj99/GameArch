
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
#include "InputTranslator.h"

static class Game : public EventListener
{
public:
	static Game* getInstance() { assert(mpGame != nullptr); return mpGame; };
	static void initInstance(EventSystem* pEventSystem) { mpGame = new Game(pEventSystem); };
	static void cleanupInstance() { delete mpGame; };


	
	void init(int = 600, int = 600);
	void cleanUp();

	void handleEvent(const Event& theEvent);


	void runGame(float fps = 60);

	System* getSystem() { return mSystem; };

private:
	Game(EventSystem* pEventSystem);
	~Game();
	UnitManager* mUnitMan;
	GraphicsBufferManager* mGBMan;
	System* mSystem;
	bool mInit = false;
	bool mExit = false;
	bool mSmurf = true;
	double mTimePerFrame;
	static Game* mpGame;
};

