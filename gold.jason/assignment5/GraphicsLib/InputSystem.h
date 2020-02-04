#pragma once

#include "EventSystem.h"
#include <allegro5/keyboard.h>
#include <allegro5/allegro_acodec.h>
#include <Trackable.h>
#include <Vector2D.h>

using namespace std;

class InputSystem : public Trackable 
{
private:
	EventSystem* mEventSys;
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_EVENT_QUEUE* mpEventQueue;


public:
	InputSystem();
	~InputSystem();

	void initInputSys();
	void getKeyState();
	void getMouseState();
	Vector2D getMouseLocation();
	void update();
	void cleanUpInput();
	EventSystem* getEventSys();


};