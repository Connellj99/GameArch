#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Timer.h>
#include <PerformanceTracker.h>
#include "Trackable.h"
#include "System.h"
#include "Unit.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "EventSystem.h"
#include "EventListener.h"
#include "InputTranslator.h"
#include "Player.h"

class EventSystem;

class Game :public EventListener
{
private:
	System* mpSys;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGBManager;
	PerformanceTracker* mpPerformanceTracker;
	Timer mTimer;
	const string mLOOP_TRACKER = "loop";
	int mHeight;
	int mWidth;
	bool mMouseDown = false;
	bool mRightMouseDown = false;
	bool mSwapNow = false;
	bool mExitNow = false;
	int mSpeedUp = 0;
	float mFramesPerSecond;

	bool mIsCleanedUp = false;
	bool mIsInitted = false;
	int* mpCurrentMousePos;
	Player* mpPlayer;

	map<string, Sprite*> mSprites;
	map<string, Animation*> mAnimations;

	vector<Sprite*> mAlwaysDraw; // For backgrounds
	vector<Unit*> mAlwaysAnimate; // For single animations
	vector<Unit*> mSwapOnEnter;

	Game(Game& game)=delete;
	static Game* mpGameInstance;

	Game();
	Game(EventSystem* pEventSystem, int width, int height, float fps = 60);
	Game(EventSystem* pEventSystem);
	~Game();

public:

	void handleEvent(const Event& theEvent);
	void handleMouseEvent(const Event& theEvent);
	void handleKeyEvent(const Event& theEvent);

	void createBuffer(string bufferName, string filename, int width, int height);
	void createAnimation(string bufferName, string filename, int dimensions);
	void createUnit(string unitName);
	void swapOnEnter(string unitName);
	void addAnimationToUnit(string unitName, string animationName);
	void drawBackground(string bufferName, int x, int y, float scale = 1.0f);
	void drawUnitAtMouse(string unitName);
	void createOnMouseDown(string unitName);
	void InstantiateAtMouse(Unit* unitName, int offset);
	static void createInstance(EventSystem* pEventSystem, int width, int height, int FPS);
	static Game* getInstance();
	static void cleanupInstance();
	void cleanup();

	void init();
	void createPlayerAtCoords(const std::string &PLAYER_BUFFER_NAME, int xLoc, int yLoc, float speed);
	void setHomeBaseBounds(float* lowerBounds, float* upperBounds);
	void doLoop();

	

};

#endif
