#pragma once
#include "allegro5/keyboard.h"
#include "allegro5/keycodes.h"
#include "allegro5/mouse_cursor.h"
#include "allegro5/mouse.h"
#include "Vector2D.h"
#include "Trackable.h"

struct Mouse
{
	bool leftDown = false;
	bool rightDown = false;
	Vector2D position;
};

struct Key
{
	bool enterDown = false;
	bool escapeDown = false;
	bool spaceDown = false;

	bool wDown = false;
	bool dDown = false;
	bool sDown = false;
	bool aDown = false;

	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};
enum KeyCode
{
	F = ALLEGRO_KEY_F,

	S = ALLEGRO_KEY_S,
	A = ALLEGRO_KEY_A,
	D = ALLEGRO_KEY_D,
	W = ALLEGRO_KEY_W,

	kDOWN = ALLEGRO_KEY_DOWN,
	kUP = ALLEGRO_KEY_UP,
	kLEFT = ALLEGRO_KEY_LEFT,
	kRIGHT = ALLEGRO_KEY_RIGHT,


	ENTER = ALLEGRO_KEY_ENTER, //Change animation

	ESCAPE = ALLEGRO_KEY_ESCAPE, //Exit program

	SPACE = ALLEGRO_KEY_SPACE// SPACE BAR
};

enum MouseCode
{
	Left_Click = 1,
	Right_Click = 2,
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	
	void update();

private:
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	ALLEGRO_MOUSE_STATE *mpMouseState;
};
