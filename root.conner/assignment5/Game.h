/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "System.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "InputTranslator.h"
#include "EventListener.h"

class Game : public EventListener
{
private:
	static Game* mpsGameObj;

	System* mpSystem;
	InputTranslator* mpInputTranslator;
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
	
	// Constructor
	Game();
	Game(Game& game) = delete;
	// Destructor
	~Game();

public:
	// Instance
	static void initInstance();
	static Game* getInstance();
	static void cleanupInstance();

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

	// Events
	void handleEvent(const Event&) override;

	// Game functions
	void spawnUnit(int, int);
	void deleteUnit(int, int);
	void speedUpAnimation();
	void slowDownAnimation();
	void togglePause();
	void toggleAnimation(); 

	bool getExitState() { return !mShouldExit; }
};