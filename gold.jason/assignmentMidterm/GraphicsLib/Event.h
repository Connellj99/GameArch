#pragma once

#include <string>
#include <Trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	LEFT_KEY,
	RIGHT_KEY,
	UP_KEY,
	DOWN_KEY,
	ESC_KEY,
	SPACE_KEY,
	R_KEY,
	N_KEY,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = 
{ 
	"Left Arrow Down",
	"Right Arrow Down",
	"Up Arrow Down",
	"Down Arrow Down",
	"Escape Down",
	"R Key Down",
	"Space Key Down",
	"N Key Down"
};

class Event :public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};