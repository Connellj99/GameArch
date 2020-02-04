#pragma once
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include "InputSystem.h"

#include "PerformanceTracker.h"
#include "MemoryTracker.h"

//allegro key codes

struct MouseState
{
	bool leftClickDown = false;
	bool rightClickDown = false;
};

class System
{
public:
	System();
	~System();

	void init(int width, int height);
	void cleanup();

	void update(double time);

	//accessor functions of various types
	bool getKeyState(int key);
	//MouseState getMouseState();
	bool getMouseState(int button);
	Vector2D getMousePos();
	GraphicsSystem* getGraphicsSystem();

private:
	bool mIsInit;

	Vector2D mMousePos;
	GraphicsSystem* mpGraphicsSystem;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	ALLEGRO_MOUSE_STATE mMouseState;

	//KeyCodes mCurrentKey;

	InputSystem* mpInputSystem;
};