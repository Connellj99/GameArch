#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <Trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT = -1,
	MOUSE_CHANGED,
	KEY_CHANGED,
	GAME_MOUSE_CHANGED,
	GAME_KEY_CHANGED,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =
{
	"Mouse Changed",
	"Game Mouse Changed",
	"Key Changed",
	"Game Key Changed"
};

class Event :public Trackable 
{
private:
	EventType mType;

public:
	Event(EventType type);
	virtual ~Event();
	EventType getType() const { return mType; }
	const string& getEventName() const;
};

#endif