#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 5
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "EventListener.h"
#include "EventSystem.h"
#include "LeftMouseEvent.h"
#include "RightMouseEvent.h"
#include "ExitGameEvent.h"
#include "AddUnitEvent.h"
#include "RemoveUnitEvent.h"
#include "SwapAnimationEvent.h"
#include "ToggleAnimationEvent.h"
#include "TurnUpEvent.h"
#include "TurnDownEvent.h"
#include "TurnLeftEvent.h"
#include "TurnRightEvent.h"
#include "StartGameEvent.h"

class InputTranslator : public EventListener
{
private:
	bool mIsInitted = false;
	EventSystem * mpEventSystem;

public:
	//init
	void init();

	//cleanup
	void cleanup();

	//constructor
	InputTranslator(EventSystem * pEventSystem);

	//destructor
	~InputTranslator();

	//handle events
	void handleEvent(const Event& theEvent);
};