#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Trackable.h"
#include "GraphicsSystem.h"
#include <allegro5/allegro.h>
#include <Timer.h>

class System :public Trackable
{
private:

	float mFramesPerSecond;
	GraphicsSystem* mpGraphicsSystem;
	ALLEGRO_EVENT_QUEUE* mpEventQueue;
	ALLEGRO_TIMER* mpTimer;
	Timer mGameTimer;
	float mMouseStateX = 0; //0,0 mouse position by default
	float mMouseStateY = 0;

public:
	System();
	System(int width, int height, float FPS);
	~System();

	void draw(int x, int y, Sprite* picture, double scale = 1.0);
	Animation* createAnimation(GraphicsBuffer* animSheet, int dimensions);
	void flip();
	int waitForEvent();
	int* getMouseState();
	void cleanup();

	void init();
	//void cleanup();
	//int getKeyState();

};

#endif
