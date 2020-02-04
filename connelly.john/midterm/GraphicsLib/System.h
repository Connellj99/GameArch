#ifndef SYSTEM_H
#define SYSTEM_H

#include "Trackable.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"

enum KeyCode
{
	F = ALLEGRO_KEY_F,
	S = ALLEGRO_KEY_S,
	ENTER = ALLEGRO_KEY_ENTER,
	ESC = ALLEGRO_KEY_ESCAPE,
	SPACE = ALLEGRO_KEY_SPACE,
	UP = ALLEGRO_KEY_UP,
	DOWN = ALLEGRO_KEY_DOWN,
	LEFT = ALLEGRO_KEY_LEFT,
	RIGHT = ALLEGRO_KEY_RIGHT,
	B = ALLEGRO_KEY_B,
	FOOD = ALLEGRO_KEY_P
};

// holds the Graphics System and has functions to get keyboard / mouse state
class System : public Trackable
{
public:
	System();
	~System();

	void init(const Vector2D& displayDimensions);
	void cleanup();
	void update(float curTime);

	GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; }
private:
	System(const System&) = delete;
	void operator=(const System&) = delete;

	bool mIsInitted = false;

	InputSystem* mpInputSystem;
	GraphicsSystem* mpGraphicsSystem;
};
#endif