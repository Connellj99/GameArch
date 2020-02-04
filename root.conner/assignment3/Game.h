/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "System.h"
#include "Unit.h"

class Game : public Trackable
{
private:
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "Woods.png";
	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string DEAN_FILENAME = "dean_sprites.png";
	
	const int SMURF_WIDTH = 60;
	const int SMURF_HEIGHT = 60;

	System* mpSystem;
	MouseState mMouseState;
	Timer* mpTimer;

	GraphicsBuffer* mpWoodsBuffer;
	GraphicsBuffer* mpSmurfBuffer;
	GraphicsBuffer* mpDeansBuffer;

	Sprite* mpWoodsSprite;
	/*Sprite* mpSmurfSprite;
	Sprite* mpDeanSprite;*/

	Animation* mpSmurfAnim;
	Animation* mpDeanAnim;

	Unit* mpCharacter;

	float mFrameRate;
	float mTimePerFrame;

	bool mInited = false;
	bool mKeyState_Exit = false;
	bool mShouldExit = false;
	bool mKeyState_F = false;
	bool mKeyState_S = false;
	bool mKeyState_Enter = false;
	bool mAnimDean = false;

public:
	// Constructor
	Game();

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
	void waitForFrame(float);

	bool getExitState() { return !mShouldExit; }

	// Destructor
	~Game();
};

extern Game* pGameObj;