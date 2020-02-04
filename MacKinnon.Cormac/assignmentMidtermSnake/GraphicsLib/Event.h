#pragma once
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <string>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>

enum KeyCodes
{
	NULL_KEY,
	F_KEY = ALLEGRO_KEY_F,
	S_KEY = ALLEGRO_KEY_S,
	R_KEY = ALLEGRO_KEY_R,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	ESCAPE_KEY = ALLEGRO_KEY_ESCAPE,
	SPACE_KEY = ALLEGRO_KEY_SPACE,
	LEFT_ARROW_KEY = ALLEGRO_KEY_LEFT,
	RIGHT_ARROW_KEY = ALLEGRO_KEY_RIGHT,
	UP_ARROW_KEY = ALLEGRO_KEY_UP,
	DOWN_ARROW_KEY = ALLEGRO_KEY_DOWN
};

enum EventType 
{
	INVALID_EVENT_TYPE = -1,
	KEY_PRESS_EVENT,
	MOUSE_PRESS_EVENT,
	NUM_EVENT_TYPES
};

const std::string EVENT_NAMES[NUM_EVENT_TYPES] = { "Key Press Event", "Mouse Press Event" };

class Event : public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	const std::string& getEventName() const;

private:
	EventType mType;
};

