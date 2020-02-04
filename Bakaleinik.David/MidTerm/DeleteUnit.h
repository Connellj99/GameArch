#pragma once
#include "Event.h"
#include "GameEvent.h"

class DeleteUnit : public Event
{
private:
	int mX;
	int mY;

public:
	DeleteUnit( int x, int y) :Event((EventType)DELETE_UNIT) { mX = x; mY = y; };
	~DeleteUnit() {};

	 int getX() const { return mX; };
	 int getY() const { return mY; };
};