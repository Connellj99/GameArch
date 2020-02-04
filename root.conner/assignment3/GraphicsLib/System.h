/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "GraphicsSystem.h"

enum KeyCode
{
	F = ALLEGRO_KEY_F,
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	ESC = ALLEGRO_KEY_ESCAPE
};

struct MouseState
{
	bool clicked = false;
	int xPos, yPos;
};

class System : public Trackable
{
private:
	GraphicsSystem* mpGraphicSystem;

	ALLEGRO_KEYBOARD_STATE mKeyState;
	ALLEGRO_MOUSE_STATE mMouseState;

	bool mInited = false;

public:
	// Constructor
	System();

	// Init / Cleanup
	void init(int, int);
	void cleanup();

	// Accessors
	GraphicsSystem* getGraphicsSystem() { return mpGraphicSystem; }
	bool checkKeyDown(KeyCode);
	MouseState checkMouseDown();

	// Wait function
	void wait(float);

	// Destructor
	~System();
};