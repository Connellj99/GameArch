#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include "Trackable.h"
#include "../Header.h"

enum keys
{
	F_KEY = ALLEGRO_KEY_F,
	S_KEY = ALLEGRO_KEY_S,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	ESCAPE_KEY = ALLEGRO_KEY_ESCAPE
};

class InputManager : public Trackable
{
private:
	ALLEGRO_MOUSE_STATE state;
	ALLEGRO_KEYBOARD_STATE keyState;

	bool pressed = false; //Keeps track if a button has been pressed during this run of the loop (Not functioning, cannot find al_key_up)

	float speedUp = 0.5; //Lower numbers speed up the loop speed faster
	float speedDown = 2.0; //Higher numbers do the opposite

public:
	InputManager();
	~InputManager();

	void init();
	void cleanup();

	void checkInput();
};