/*
Conner Root
EGP 310-01
*/

#pragma once

#include <Trackable.h>
#include "GraphicsLib.h"

struct MouseState
{
	bool lClicked = false;
	bool rClicked = false;
	int xPos, yPos;
};

class InputSystem : public Trackable
{
private:
	ALLEGRO_EVENT_QUEUE* mpEventQueue;
	
	bool mInited = false;

public:
	// Constructor
	InputSystem();

	// Init/Cleanup
	void init();
	void cleanup();

	// Update
	void update(); // Move System input here; change to fire events 
	
	// Destructor
	~InputSystem();
};