#pragma once

#include <string>
#include <Trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	LEFT_CLICK,
	RIGHT_CLICK,
	SPACE_KEY,
	ESC_KEY,
	ENTER_KEY,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = 
{ 
	"Left Click",
	"Right Click",
	"Spacebar Down",
	"Escape Down",
	"Enter Down"
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