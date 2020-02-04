#include "KeyPressEvent.h"



KeyPressEvent::KeyPressEvent(int keyValue) 
	: Event(KEY_PRESS_EVENT)
{
	mKeyPressed = keyValue;
}

KeyPressEvent::~KeyPressEvent()
{
}

int KeyPressEvent::getPressedKey() const
{
	return mKeyPressed;
}
