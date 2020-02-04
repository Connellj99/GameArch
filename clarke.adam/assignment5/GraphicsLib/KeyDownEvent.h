#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include "Event.h"
#include "System.h"

class KeyDownEvent : public Event
{
public:
	KeyDownEvent(KeyCode keyCode) : Event(KEY_DOWN_EVENT), mKeyCode(keyCode) {}

	KeyCode getKeyCode() const { return mKeyCode; }
private:
	KeyCode mKeyCode;
};
#endif