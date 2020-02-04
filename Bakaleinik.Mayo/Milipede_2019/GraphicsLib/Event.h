#pragma once

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	SPACE,
	O_KEY,
	D_KEY,
	L_KEY,
	S_KEY,
	ESCAPE,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =	{	"Shoot", "Options", "Difficulty", "Load", "Start", "Quit" };

class Event:public Trackable
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};