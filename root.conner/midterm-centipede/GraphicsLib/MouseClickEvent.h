/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "Event.h"

class MouseClickEvent : public Event
{
private:
	int mMouseButton, mXPos, mYPos;

public:
	MouseClickEvent(int mouse, int x, int y) : Event(MOUSE_CLICK_EVENT),
		mMouseButton(mouse), mXPos(x), mYPos(y) {}

	int getMouseButtonDown() { return mMouseButton; }
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	~MouseClickEvent() {}
};