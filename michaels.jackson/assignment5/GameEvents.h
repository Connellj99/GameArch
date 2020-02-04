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
/*
SPAWN_UNIT,
DELETE_UNIT,
STOP_ANIM,
CHANGE_ANIM,
EXIT,
*/
class SpawnEvent : public Event
{
public:
	SpawnEvent(Point key = Point()) :Event(SPAWN_UNIT), loc(key) {}
	~SpawnEvent() {}

	inline Point getLoc() const { return loc; };

private:
	Point loc;
};

class DeleteEvent : public Event
{
public:
	DeleteEvent(Point key) :Event(DELETE_UNIT), loc(key) {}
	~DeleteEvent() {}

	inline Point getLoc() const { return loc; };

private:
	Point loc;
};

class StopEvent : public Event
{
public:
	StopEvent() :Event(STOP_ANIM) {}
	~StopEvent() {}

private:
};

class ChangeEvent : public Event
{
public:
	ChangeEvent() :Event(CHANGE_ANIM) {}
	~ChangeEvent() {}

private:
};

class ExitEvent : public Event
{
public:
	ExitEvent() :Event(EXIT) {}
	~ExitEvent() {}

private:
};