/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "System.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"

class Game : public Trackable
{
private:
	static Game* mpsGameObj;

	System* mpSystem;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpBufferManager;
	Timer* mpTimer;
	Sprite* mpBackground;

	MouseState mMouseState;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "Woods.png";
	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string DEAN_FILENAME = "dean_sprites.png";

	float mFrameRate;
	float mTimePerFrame;

	bool mInited = false;
	bool mShouldExit = false;

public:
	// Constructor
	Game();

	// Instance
	static void initInstance();
	static Game* getInstance();

	// Init / Cleanup
	void init(int, int, float);
	void cleanup();

	// Accessors
	System* getSystem() { return mpSystem; }

	// Game Loop
	void gameLoop();
	void getInput();
	void update();
	void drawScene();

	bool getExitState() { return !mShouldExit; }

	// Destructor
	~Game();
};