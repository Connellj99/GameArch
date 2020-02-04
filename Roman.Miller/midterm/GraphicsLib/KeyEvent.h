#pragma once
#include "Event.h"
#include "InputSystem.h"
using namespace std;


class KeyEvent : public Event
{
public:
	KeyEvent(const Key& code);
	~KeyEvent();

	Key getKeyCode() const { return mKey; };

private:
	Key mKey;
};
