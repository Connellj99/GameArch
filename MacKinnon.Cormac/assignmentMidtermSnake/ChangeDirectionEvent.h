#pragma once
#include "Event.h"
#include "GameEvents.h"

class ChangeDirectionEvent : public Event
{
public:
	ChangeDirectionEvent(int x, int y);
	~ChangeDirectionEvent();

	int getX() const { return mXValue; };
	int getY() const { return mYValue; };

private:
	int mXValue;
	int mYValue;
};

