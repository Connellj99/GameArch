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

	void updateInputGame();//the update function that will get the input from allegro
	void updateInputStart();//the update function that will get the input from allegro for the start of the game
	void updateInputEnd();//update function that will get the input from allegro for the end of the game

	//Accessors
	void getKeyState();
	void getKeyStateGame();//this is to limit player to only pressing the buttons such as continue, or movement
	void getKeyStateEnd();//this is to limit player to pressing only two buttons, end or restart
	void getArrowState();
	void getMouseState();
	
private:

	//bools to set if the escape, space, or enter button has already been pressed(or R)
	bool mHitEscape;
	bool mHitSpace;
	bool mHitEnter;
	bool mHitR;
	
	//bool to set if the arrow keys have been pressed
	bool mHitLeftArrow;
	bool mHitRightArrow;
	bool mHitUpArrow;
	bool mHitDownArrow;
};

#endif