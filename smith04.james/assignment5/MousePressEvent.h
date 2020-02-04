#pragma once

#include "Event.h"

class MousePressEvent : public Event
{
public:
	MousePressEvent(int state, float xLoc, float yLoc);
	~MousePressEvent();

	int getState() const { return mState; };
	float getX() const { return x; };
	float getY() const { return y; };

private:
	int mState;
	float x;
	float y;
};