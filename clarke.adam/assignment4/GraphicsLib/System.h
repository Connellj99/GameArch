#ifndef SYSTEM_H
#define SYSTEM_H

#include "Trackable.h"
#include "GraphicsSystem.h"

enum KeyCode
{
	F = ALLEGRO_KEY_F,
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	ESC = ALLEGRO_KEY_ESCAPE,
	SPACE = ALLEGRO_KEY_SPACE
};

struct MouseState
{
	bool m1IsDown = false;
	bool m2IsDown = false;
	Vector2D location;
};

// holds the Graphics System and has functions to get keyboard / mouse state
class System : public Trackable
{
public:
	System();
	~System();

	void init(const Vector2D& displayDimensions);
	void cleanup();

	GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; }
	bool getKeyState(KeyCode keyCode);
	MouseState getMouseState();
private:
	System(const System&) = delete;
	void operator=(const System&) = delete;

	bool mIsInitted = false;

	GraphicsSystem* mpGraphicsSystem;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	ALLEGRO_MOUSE_STATE mMouseState;
};
#endif