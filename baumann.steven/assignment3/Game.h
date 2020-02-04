#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Timer.h>
#include <PerformanceTracker.h>
#include "Trackable.h"
#include "System.h"
#include "Unit.h"

class Game :public Trackable
{
private:
	System* mpSys;
	PerformanceTracker* mpPerformanceTracker;
	Timer mTimer;
	const string mLOOP_TRACKER = "loop";
	int mHeight;
	int mWidth;
	bool mMouseDown = false;
	bool mSwapNow = false;
	bool mExitNow = false;
	int mSpeedUp = 0;
	float mFramesPerSecond;

	int* mpCurrentMousePos;

	map<string, GraphicsBuffer*> mBuffers;
	map<string, Sprite*> mSprites;
	map<string, Animation*> mAnimations;
	map<string, Unit*> mUnits;

	vector<Sprite*> mAlwaysDraw;
	vector<Unit*> mAlwaysAnimate;
	vector<Unit*> mSwapOnEnter;

	void Game::drawAnimation(Unit* animName, float scale, float offset);
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
	void cleanup();


	void init();
	void doLoop();

};

#endif
