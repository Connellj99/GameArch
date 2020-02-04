#pragma once
#include "GraphicsSystem.h"
#include "Vector2D.h"

#include "PerformanceTracker.h"
#include "MemoryTracker.h"

//allegro key codes
enum KeyCodes 
{
	NULL_KEY,
	F_KEY = ALLEGRO_KEY_F,
	S_KEY = ALLEGRO_KEY_S,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	ESCAPE_KEY = ALLEGRO_KEY_ESCAPE
};



class System
{
public:
	System();
	~System();

	void init(int width, int height);
	void cleanup();

	//accessor functions of various types
	bool getKeyState(int key);
	bool getMouseState();
	Vector2D getMousePos();
	GraphicsSystem* getGraphicsSystem();

private:
	bool mIsInit;

	Vector2D mMousePos;
	GraphicsSystem* mpGraphicsSystem;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	ALLEGRO_MOUSE_STATE mMouseState;

	KeyCodes mCurrentKey;

	
};