/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "InputSystem.h"
#include "GameEvents.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <allegro5/allegro.h>
class InputTranslator : public EventListener
{
public:
	InputTranslator(EventSystem* pEventSystem);
	~InputTranslator() {}

	void init();
	void cleanUp();
	void update();

	void handleEvent(const Event& theEvent);

private:
	EventSystem* mpEventSys;
};