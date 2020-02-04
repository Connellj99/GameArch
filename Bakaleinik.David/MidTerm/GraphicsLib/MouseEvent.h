#pragma once

#include "Event.h"

class MouseEvent : public Event
{
private:
	int mX;
	int mY;

	int mMouseButton;

public:

	int getX() const { return mX; };
	int getY() const { return mY; };

	int getButton() const { return mMouseButton; };

	MouseEvent(int x, int y, EventType name, int button) :Event(name) { mX = x; mY = y; mMouseButton = button; };
	~MouseEvent() {};
};