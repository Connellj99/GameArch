/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "GraphicsSystem.h"
#include "InputSystem.h"



class System : public Trackable
{
public:
	System();
	~System();

	int init(int = 100, int = 100);
	int cleanUp();

	void rest(double);
	void clear() { al_clear_to_color(al_map_rgba_f(0.0, 0.0, 0.0, 1.0)); };

	void update() { mInSys.update(); }

	GraphicsSystem mGraphics;

private:
	InputSystem mInSys;
	bool mInit;

};