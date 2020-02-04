#pragma once
#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "GraphicsSystem.h"
#include <Trackable.h>
#include <allegro5/allegro.h>

class InputSystem :public Trackable 
{
private:
	ALLEGRO_EVENT_QUEUE* mpEventQueue;
	ALLEGRO_TIMER* mpTimer;
	int mMouseStateX = 0; //0,0 mouse position by default
	int mMouseStateY = 0;
	bool mIsCleaned;
public:

	InputSystem();
	InputSystem(GraphicsSystem* displaySystem);
	~InputSystem();
	
	void init(GraphicsSystem* displaySystem, ALLEGRO_TIMER* mpTimer);
	void update();
	void cleanup();
	int* getMouseState();


};

#endif