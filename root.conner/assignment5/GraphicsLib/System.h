/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "GraphicsSystem.h"
#include "InputSystem.h"

enum KeyCode
{
	F = ALLEGRO_KEY_F,
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	ESC = ALLEGRO_KEY_ESCAPE,
	SPACE = ALLEGRO_KEY_SPACE
};

class System : public Trackable
{
private:
	GraphicsSystem* mpGraphicSystem;
	InputSystem* mpInputSystem;

	bool mInited = false;

public:
	// Constructor
	System();

	// Init / Cleanup
	void init(int, int);
	void cleanup();

	// Accessors
	GraphicsSystem* getGraphicsSystem() { return mpGraphicSystem; }
	InputSystem* getInputSystem() { return mpInputSystem; }

	// Wait function
	void wait(float);

	// Destructor
	~System();
};