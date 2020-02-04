#pragma once
#include "Event.h"

class KeyEvent : public Event
{
public:
	KeyEvent(bool isDown, EventType name):Event(name) { keyDown = isDown; };
	~KeyEvent() {};

	bool getKeyStatus() const { return keyDown; };
private:

	bool keyDown;
};