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
	Font* mpFontCour;

	MouseState mMouseState;
	Color mFontColor;

	string AssetPath;
	string BackgroundFilename;
	string PlayerFilename;
	string BulletFilename;
	string MushroomFilename;
	string CentipedeHeadFilename;
	string CentipedeBodyFilename;
	string CourFontFilename;

	float mFrameRate;
	float mTimePerFrame;
	float mCurrFPS;

	bool mInited = false;
	bool mPlaying = false;
	bool mEnded = false;
	bool mShouldExit = false;
	
	int mDispWidth, mDispHeight;
	int mLives = 3;
	int mScore = 0;
	int mExtraLives = 0;

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
	void init();
	void cleanup();

	// Accessors
	System* getSystem() { return mpSystem; }

	// Game Loop
	void gameLoop();
	void update();
	void drawScene();

	// Events
	void handleEvent(const Event&) override;

	// Game functions
	void startGame();
	void endGame();
	
	void addToScore(char f);
	void movePlayer(int, int);
	void deleteUnit(int, int);
	void killPlayer();
	
	/*
	void togglePlaying();
	void spawnUnit(int, int);
	void speedUpAnimation();
	void slowDownAnimation();
	void toggleAnimation(); 
	*/

	bool getExitState() { return !mShouldExit; }
};