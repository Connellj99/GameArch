#pragma once
#include "Trackable.h"
#include "System.h"


class EventSystem;
class System;

class InputSystem : public Trackable
{
private:

	EventSystem* mpEventSystem;
	System* mpSystem;

	ALLEGRO_KEYBOARD_STATE mLastKeyState;
	ALLEGRO_MOUSE_STATE mLastMouseState;
	
	bool inFirstUpdate = true;

public:
	
	InputSystem();
	//InputSystem();
	~InputSystem();


	void init(System* gameSystem, EventSystem* eventSystem);
	void update();
	void cleanup();
};