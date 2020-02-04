#pragma once
#include "Event.h"

class RightMouseEvent : public Event
{
private:
	int mX;
	int mY;

public:
	
	 int getX() const { return mX; };
	 int getY() const { return mY; };
	
	RightMouseEvent(int x, int y);
	~RightMouseEvent();
};