#pragma once
#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event.h"

enum KeyType { INVALID_KEY_TYPE = -1, ENTER_KEY, F_KEY, S_KEY, ESCAPE_KEY, SPACE_KEY, UP_KEY, LEFT_KEY, DOWN_KEY, RIGHT_KEY, ENTER_KEY_UP, F_KEY_UP, S_KEY_UP, ESCAPE_KEY_UP, SPACE_KEY_UP, UP_KEY_UP, LEFT_KEY_UP, DOWN_KEY_UP, RIGHT_KEY_UP, NUM_KEY_TYPES };

class KeyEvent :public Event 
{
private:
	KeyType mbType;

public:


	KeyEvent(const KeyType& mb);
	~KeyEvent();

	KeyType getButtonType() const { return mbType; }
};

#endif