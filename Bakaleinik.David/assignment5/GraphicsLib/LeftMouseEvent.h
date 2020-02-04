#pragma once
#include "Event.h"

class LeftMouseEvent : public Event
{
	
private:
	int mX;
	int mY;

public:

	 int getX() const { return mX; };
	 int getY() const { return mY; };

	LeftMouseEvent(int x, int y);
	~LeftMouseEvent();

};