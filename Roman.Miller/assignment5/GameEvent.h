#pragma once
#include "Event.h"
#include "Vector2D.h"

enum GameEventType
{
	EXIT_GAME = NUM_EVENT_SIZE,
	CREATE,
	DESTROY,
	PAUSE_ANIMATIONS,
	SWAP_ANIMATIONS
};

class UnitEvent: public Event
{
public:
	UnitEvent(const Vector2D& loc);
	~UnitEvent();

	Vector2D getLocation() const { return mLoc; };
private:
	Vector2D mLoc;
};

class DestroyEvent: public Event
{
public:
	DestroyEvent(const Vector2D& loc);
	~DestroyEvent();

	Vector2D getLocation() const { return mLoc; };

private:
	Vector2D mLoc;
};