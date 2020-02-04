#pragma once
#include "Event.h"
#include "GameEvent.h"

class CreateUnit : public Event
{
private:
	int mX;
	int mY;

public:
	CreateUnit( int x, int y) :Event((EventType)CREATE_UNIT) { mX = x; mY = y; };
	~CreateUnit() {};

	 int getX() const { return mX; };
	 int getY() const { return mY; };
};