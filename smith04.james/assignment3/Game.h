#pragma once
#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "Unit.h"
#include "PerformanceTracker.h"
#include "Timer.h"

class InputManager;

class Game : public Trackable
{
private:
	System* mpGameSys;
	float timeScale;
	bool exit = false;

	GraphicsBuffer* woodsBuffer;
	GraphicsBuffer* smurfBuffer;
	GraphicsBuffer* deanBuffer;

	const std::string ASSET_PATH = "..\\..\\shared\\assets";
	const std::string WOODS_PATH = ASSET_PATH + "\\Woods.png";
	const std::string SMURF_PATH = ASSET_PATH + "\\smurf_sprites.png";
	const std::string DEAN_PATH = ASSET_PATH + "\\dean_sprites.png";

	const std::string INIT_TRACKER_NAME = "init";
	const std::string DRAW_TRACKER_NAME = "draw";
	const std::string WAIT_TRACKER_NAME = "wait";

	InputManager* mpInputManager;

	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();
	Timer* timer = new Timer();

	//Tracks if Unit is Dean smurf
	bool isDean = false;

public:
	Game(float w, float h, float t);
	~Game();

	void init(float w, float h, float t);
	void cleanup();

	void gameLoop();

	void getInput();
	
	void update();
	
	void render();

	Unit* smurfUnit;

	void shouldExit();

	void adjustTime(float change);

	void switchAnim();
};

#endif