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

class Game :public Trackable
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

	map<string, Sprite*> mSprites;
	map<string, Animation*> mAnimations;

	vector<Sprite*> mAlwaysDraw; // For backgrounds
	vector<Unit*> mAlwaysAnimate; // For single animations
	vector<Unit*> mSwapOnEnter;
public:
	Game();
	Game(int width, int height, float fps = 60);
	~Game();

	void createBuffer(string bufferName, string filename, int width, int height);
	void createAnimation(string bufferName, string filename, int dimensions);
	void createUnit(string unitName);
	void swapOnEnter(string unitName);
	void addAnimationToUnit(string unitName, string animationName);
	void drawBackground(string bufferName, int x, int y, float scale = 1.0f);
	void drawUnitAtMouse(string unitName);
	void createOnMouseDown(string unitName);
	void InstantiateAtMouse(Unit* unitName, int offset);
	void cleanup();

	void init();
	void doLoop();

	static Game* mpGameInstance;

};

#endif
