#pragma once

#include "Event.h"

class DeleteEvent : public Event
{
public:
	DeleteEvent(float xLoc, float yLoc);
	~DeleteEvent();

	float getX() const { return x; };
	float getY() const { return y; };

private:
	float x;
	float y;
};