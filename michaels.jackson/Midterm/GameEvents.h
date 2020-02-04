/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

#include "Event.h"
#include "Constants.h"
#include <string>

using namespace std;
enum Direction
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

enum PowerUp {
	SPEED_UP = 0,
	SLOW_DOWN,
	GET_POINTS,
	GROW,
	NUM_TYPE
};

class MoveEvent : public Event
{
public:
	MoveEvent(int dir) :Event(MOVE_EVENT), mDIr(dir) {}
	~MoveEvent() {}

	inline int getDir() const { return mDIr; };

private:
	int mDIr;
};

class PowerUpEvent : public Event
{
public:
	PowerUpEvent(PowerUp type) :Event(POWER_UP_EVENT), mPower(type) {}
	~PowerUpEvent() {}
	inline PowerUp getPower() const { return mPower; };
private:
	PowerUp mPower;
};

class GameOverEvent : public Event
{
public:
	GameOverEvent() :Event(GAME_OVER_EVENT) {}
	~GameOverEvent() {}

};

class GrowEvent : public Event
{
public:
	GrowEvent() :Event(GROW_EVENT) {}
	~GrowEvent() {}


};

class ContinueEvent : public Event
{
public:
	ContinueEvent() :Event(CONTINUE_EVENT) {}
	~ContinueEvent() {}


};

class ExitEvent : public Event
{
public:
	ExitEvent() :Event(EXIT) {}
	~ExitEvent() {}

private:
};