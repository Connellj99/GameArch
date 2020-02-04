#ifndef SYSTEM_H
#define SYSTEM_H

#include "Trackable.h"
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
	bool isDown = false;
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
	MouseState getMouseState(int mouseButton);
private:
	System(const System&);
	void operator=(const System&);

	bool mIsInitted = false;

	GraphicsSystem* mpGraphicsSystem;
	ALLEGRO_KEYBOARD_STATE mKeyboardState;
	ALLEGRO_MOUSE_STATE mMouseState;
};
#endif