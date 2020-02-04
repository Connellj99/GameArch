/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "Event.h"
#include "System.h"

class KeyDownEvent : public Event
{
private:
	KeyCode mKeyCode;

public:
	KeyDownEvent(KeyCode code) : Event(KEY_DOWN_EVENT), mKeyCode(code) {}

	KeyCode getKeyCode() { return mKeyCode; }
};