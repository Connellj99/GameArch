#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <trackable.h>

using namespace std;

//enums that contain my state of button events
enum EventType
{
	INVALID_EVENT = -1,
	//keyboard inputs
	ENTER_BUTTON_RELEASED,
	SPACE_BUTTON_RELEASED,
	ESCAPE_BUTTON_RELEASED,
	R_BUTTON_RELEASED,
	//arrow key inputs
	LEFT_ARROW_RELEASED,
	RIGHT_ARROW_RELEASED,
	UP_ARROW_RELEASED,
	DOWN_ARROW_RELEASED,
	//mouse inputs
	LEFT_CLICK_PRESSED,
	RIGHT_CLICK_PRESSED,
	NUM_EVENT_TYPES,
};

//event names in case I want to see the names of what was pressed
const string EVENT_NAMES[NUM_EVENT_TYPES] = { "Enter Key Pressed",
"Space Key Pressed",
"Escape Key Pressed",
"Left Arrow Pressed",
"Right Arrow Pressed",
"Up Arrow Pressed",
"Down Arrow Pressed",
"Left Mouse Pressed",
"Right Mouse Pressed",
};


class Event:public Trackable
{
public:
	Event();//default constructor
	Event( EventType type );
	virtual ~Event();//destructor for polymorphs

	EventType getType() const { return mEventType; };
	const string& getEventName() const;

private:
	EventType mEventType;

};
#endif