/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "Constants.h"
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <allegro5/allegro.h>

class Color : public Trackable 
{
	friend class GraphicsBuffer;
	friend class GraphicsSystem;
private:
	ALLEGRO_COLOR mAlColor;
	ALLEGRO_COLOR getAllegroColor() { return mAlColor; }
	void makeAlColor(float, float, float, float);
public:
	float mR, mG, mB, mA;
	Color();
	Color(int, int, int, int = 255);
	Color(float, float, float, float = 1.0f);
	~Color();
};