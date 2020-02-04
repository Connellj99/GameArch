#pragma once

#include "allegro5/keyboard.h"
#include "allegro5/keycodes.h"
#include "allegro5/mouse_cursor.h"
#include "allegro5/mouse.h"
#include "GraphicsSystem.h"
#include "Trackable.h"






class System : public Trackable
{
public:
	System();
	~System();

	void init();
	void cleanup();

	GraphicsSystem* getGraphicsSystem();
	Vector2D getDisplaySize();

	//bool getKeyDown(KeyCode keyCode);
	//Mouse getButtonDown(MouseCode);

private:
	//Graphics System Object
	GraphicsSystem* mGraphicsSystem;
	//Frame Rate Goal
	double mFrameRate;
	//Display Size
	Vector2D mDisplaySize;

	//ALLEGRO_KEYBOARD_STATE mKeyboardState;
	//ALLEGRO_MOUSE_STATE *mMouseState;

};