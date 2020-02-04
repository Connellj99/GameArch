#pragma once
#include <string>
#include "Trackable.h"
#include "GraphicsSystem.h"
#include "Sprite.h"

//class GSystem;
class InputSystem;

class System : public Trackable		//The class which holds the Graphics System and has functions to get keyboard/mouse state – part of GraphicsLib project.
{
	friend class InputSystem;

private:

	GSystem* mDisplay;

	ALLEGRO_MOUSE_STATE mPlayerMouse;
	ALLEGRO_KEYBOARD_STATE mPlayerKeyboard;

	bool mIsInited = false;

	

public:

	System();
	System(int h, int w);
	~System();

	int getMouseX();
	int getMouseY();
	
	void initSystem();
	void cleanupSystem();

	int getMouseState();
	string getKeyState(); // call get key state at the start; then use al key down to check which were pressed
	GSystem* getDisplay() { return mDisplay; };
	void sleep(double time);
};