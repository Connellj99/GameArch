/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#pragma once
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Animation.h"
#include "GraphicsSystem.h"
//#include <allegro5/allegro.h>

struct Point
{
	float x, y;
};

struct MouseState
{
	bool left, right;
	Point loc;
};

enum KeyConvert
{
	KEY_F = ALLEGRO_KEY_F,
	KEY_S = ALLEGRO_KEY_S,
	KEY_ENTER = ALLEGRO_KEY_ENTER,
	KEY_ESCAPE = ALLEGRO_KEY_ESCAPE
};

class System : public Trackable
{
public:

	System();
	~System();
	int init(int = 100, int = 100);
	int cleanUp();
	bool getKeyState(KeyConvert);
	MouseState getMouseState();
	void rest(double time);
	//void clear() { al_clear_to_color(al_map_rgba_f(1.0, 1.0, 1.0, 1.0)); };
	GraphicsSystem mGraphics;

private:
	
	ALLEGRO_KEYBOARD_STATE mpkeyboardState;
	bool mInit;
	bool pressed_keys[ALLEGRO_KEY_MAX];
};