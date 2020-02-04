#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "System.h"

#include "Event.h"

#include "EventSystem.h"

#include "LeftClikEvent.h"
#include "RIghtClikEvent.h"

class System;

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void initInputSystem();

	void updateInput();//the update function that will get the input from allegro

	//Acessors
	void getKeyState();
	void getMouseState();
	
private:

	//bools to set if the escape space or enter button has already been pressed
	bool mHitEscape;
	bool mHitSpace;
	bool mHitEnter;
};

#endif