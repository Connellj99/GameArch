#pragma once
#include "Event.h"

class KeyPressEvent : public Event
{
public:
	KeyPressEvent(int keyValue);
	~KeyPressEvent();

	int getPressedKey() const;

private:
	int mKeyPressed;
};

