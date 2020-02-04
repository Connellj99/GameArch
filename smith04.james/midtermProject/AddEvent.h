#pragma once

#include "Event.h"

class AddEvent : public Event
{
public:
	AddEvent(float xLoc, float yLoc);
	~AddEvent();

	float getX() const { return x; };
	float getY() const { return y; };

private:
	float x;
	float y;
};