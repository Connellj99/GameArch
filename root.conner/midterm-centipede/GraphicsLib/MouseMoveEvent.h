/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "Event.h"

class MouseMoveEvent : public Event
{
private:
	int mXPos, mYPos;

public:
	MouseMoveEvent(int x, int y) : Event(MOUSE_MOVE_EVENT),
		mXPos(x), mYPos(y) {}

	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	~MouseMoveEvent() {}
};