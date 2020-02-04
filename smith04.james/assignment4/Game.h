#pragma once
#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "PerformanceTracker.h"
#include "Timer.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"

class InputManager;

class Game : public Trackable
{
private:
	Game();

	static Game* mpGameInstance;

	System* mpGameSys;
	float mTimeScale;
	bool mExit = false;

	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpBufferManager;

	//GraphicsBuffer* mpWoodsBuffer;
	//GraphicsBuffer* mpSmurfBuffer;
	//GraphicsBuffer* mpDeanBuffer;

	const std::string ASSET_PATH = "..\\..\\shared\\assets";
	const std::string WOODS_PATH = ASSET_PATH + "\\Woods.png";
	const std::string SMURF_PATH = ASSET_PATH + "\\smurf_sprites.png";
	const std::string DEAN_PATH = ASSET_PATH + "\\dean_sprites.png";

	const std::string INIT_TRACKER_NAME = "init";
	const std::string DRAW_TRACKER_NAME = "draw";
	const std::string WAIT_TRACKER_NAME = "wait";

	InputManager* mpInputManager;

	PerformanceTracker* mpPerformanceTracker = new PerformanceTracker();
	Timer* mpTimer = new Timer();

	//Tracks if Unit is Dean smurf
	bool mIsDean = false;
	bool mUnitUpdate = true;

public:
	~Game();

	void init(float w, float h, float t);
	void cleanup();

	void gameLoop();

	void getInput();
	
	void update();
	
	void render();

	void shouldExit();

	void adjustTime(float change);

	void switchAnim();

	void addSmurf(float x, float y);
	void removeUnitAt(float x, float y);

	void enableUnitUpdating();

	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();
};

#endif