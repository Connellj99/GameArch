#pragma once
#include "Event.h"
#include "Vector2D.h"

enum GameEventType
{
	EXIT_GAME = NUM_EVENT_SIZE,
	START,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DESTROY_FOOD,
	CREATE_FOOD,
	DRESTROY_POWERUP,
	CREATE_POWERUP,
	EAT,
	SPEED,
	SLOW
};

class CreateFoodEvent : public Event
{
public:
	CreateFoodEvent(const Vector2D& loc);
	~CreateFoodEvent();
	Vector2D getLocation() const { return mLoc; };

private:
	Vector2D mLoc;
};

class DestroyFoodEvent: public Event
{
public:
	DestroyFoodEvent(const Vector2D& loc);
	~DestroyFoodEvent();

	Vector2D getLocation() const { return mLoc; };

private:
	Vector2D mLoc;
};

class DestroyPowerEvent: public Event
{
public:
	DestroyPowerEvent();
	~DestroyPowerEvent();

	Vector2D getLocation() const { return mLoc; };

private:
	Vector2D mLoc;

};

class CreatePowerEvent: public Event
{
public:
	CreatePowerEvent();
	~CreatePowerEvent();

	Vector2D getLocation() const { return mLoc; };

private:
	Vector2D mLoc;
};