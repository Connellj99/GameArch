#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Trackable.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include <allegro5/allegro.h>
#include <Timer.h>

class System :public Trackable
{
private:

	float mFramesPerSecond;
	InputSystem* mpInSystem;
	GraphicsSystem* mpGraphicsSystem;
	Timer mGameTimer;
	int mMouseStateX = 0; //0,0 mouse position by default
	int mMouseStateY = 0;
	bool mIsCleaned = false;

public:
	System();
	System(int width, int height, float FPS);
	~System();

	enum eventType {MouseChanged, EnterKey, FKey, SKey, EscapeKey, SpaceKey, RemoveSprite, SpeedUp, SlowDown, NoEvent};

	void draw(int x, int y, Sprite* picture, double scale = 1.0);
	Animation* createAnimation(GraphicsBuffer* animSheet, vector<GraphicsBuffer*> &targetSheet, int dimensions);
	GraphicsBuffer* createAnimation(GraphicsBuffer* animSheet,  int dimensions);
	void flip();
	void waitForEvent();
	int* getMouseState();
	void cleanup();
	void init();

};

#endif
