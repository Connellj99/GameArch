#include "KeyEvent.h"

KeyEvent::KeyEvent(const KeyType& kt)
	: Event(KEY_CHANGED), mbType(kt)
{
}

KeyEvent::~KeyEvent()
{
}